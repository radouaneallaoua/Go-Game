#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
int M=0;
int FIN=1;
int score1=0,score2=0;
typedef struct{
    int number;
    int color;
    int visited;
}stone;
void show( stone goban[81],int score1,int score2);
void creation(stone goban[81]);
void slogan();
int est_vide(stone goban[81]);
void take_position(stone goban[81],int player,int position,int *tab1,int *tab2);
void Color(int couleurDuTexte,int couleurDeFond);
void colorplayer(int p);
int number_of_liberties(stone goban[81],int position);
int above_position(int position);
int under_position(int position);
int right_position(int position);
int left_position(int position);
void defence(stone goban[81],int player);
int enemy(stone goban[81],int position);
int numbers_voisin(stone goban[81],int position);
int *tabami(stone goban[81],int position);
int *tab_enemy(stone goban[81],int position);
int in_table(int *tab,int position);
int number_of_stones_exist_in_the_goban(stone goban[81],int player);
void save(stone goban[81],int *tab);
void  identifier_groupe(stone goban[81], int position,int *tab);
void chaine_complete(stone goban[81],int position,int *tab_positions_chaine);
int *chaine_liberties(stone goban[81],int *tab_positions_chaine);
int *tab_liberties(stone goban[81],int position);
int number_liberties_chaine(stone goban[81],int *tab);
void capture_chaine(stone goban[81],int player,int position);
void machine_joueur(stone goban[81]);
void joueur_joueur(stone goban[81]);
int ko_check(int *tab1,int *tab2);
void tremove2(stone goban[81],int position);
void remove_chaine(stone goban[81],int *tab_positions);
int attaque(stone goban[81],int player1);
void machine_intelligente(stone goban[81]);
void defence(stone goban[81],int player);
int main()
{
    int choix1,choix2;
    system("color 9");
    slogan();
    stone goban[81];
    creation(goban);
    affiche_menu1();
    printf("\t\t\t\t\t");
    printf("Please enter your choice >>>\t");
    scanf("%d",&choix1);
    switch(choix1){
    case 1:{
        system("@cls||clear");
        affiche_menu2();
        printf("\n\n\t\t\t\t\t");
        printf("Please enter your choice >>>\t");
        scanf("%d",&choix2);
        switch (choix2){
            case 1:{
                 system("@cls||clear");
                 joueur_joueur(goban);
            }
            case 2:{
                system("@cls||clear");
                machine_joueur(goban);
            }
            case 3:{
                 system("@cls||clear");
                 machine_intelligente(goban);
             }
         }
         break;
      }
        case 2:{
            system("@cls||clear");
            rules_of_GO();
        }
        case 3:{
            EXIT_FAILURE;
        }
    }
}
void joueur_joueur(stone goban[81]){//fonction joueur VS joueur
    int position;
    int player1,player2;
    srand(time(NULL));
    player1=rand()%2+1;
    player2=3-player1;
    show(goban,score1,score2);
    printf("\t\t\t the player who will play first is >>>>\t%d\n\n",player1);
    while(FIN==1){
        int *tab1=(int *)calloc(81,sizeof(int));
        int *tab2=(int *)calloc(81,sizeof(int));
        take_position(goban,player1,position,tab1,tab2);
        take_position(goban,player2,position,tab1,tab2);
    }
    if(score1>score2){
        Color(1,0);
        printf("\n\n the player who is win is (.:.) >>>>>> %d",1);
    }else{
        Color(2,0);
        printf("\n\n the player who is win is (.:.) >>>>>> %d",2);
    }
}
void creation(stone goban[81]){//initialisation du goban pour jouer
    int i;
    for(i=0;i<=80;i++){
            goban[i].number=i+1;
            goban[i].color=0;
            goban[i].visited=0;
    }
}
void show( stone goban[81],int score1,int score2){//fonction d'affichage de goban ainsi que les scores des joueurs
    int i;
    printf("\n\t\t\t");
    for(i=0;i<=80;i++){
           if(goban[i].color==0){
                if(goban[i].number<=8){
                     printf("%d  ----- ",goban[i].number);
                }else if(goban[i].number%9==0){
                      printf("%d\n\t\t\t",goban[i].number);
                      if(goban[i].number<81){
                            printf("|        |        |        |        |        |        |        |        |\n\t\t\t");
                            printf("|        |        |        |        |        |        |        |        |\n\t\t\t");
                      }
                }else{
                  printf("%d ----- ",goban[i].number);
               }
           }else{
                if(goban[i].number<=8){
                     colorplayer(goban[i].color);
                     printf("  ----- ");
                }else if(goban[i].number%9==0){
                      colorplayer(goban[i].color);
                      printf("\n\t\t\t");
                      if(goban[i].number<81){
                            printf("|        |        |        |        |        |        |        |        |\n\t\t\t");
                            printf("|        |        |        |        |        |        |        |        |\n\t\t\t");
                      }
                }else{
                  colorplayer(goban[i].color);
                  printf(" ----- ");
               }
        }
    }
    Color(15,0);
    printf("\n\n\t\t player 1 >>>\t score %d \t stones %d",score1,number_of_stones_exist_in_the_goban(goban,1));
    Color(11,0);
    printf("\n\n\t\t player 2 >>>\t score %d \t stones %d",score2,number_of_stones_exist_in_the_goban(goban,2));
}
void slogan(){
       printf("\n\n");
       printf("                                                  _/_/_/    _/ _/                                      \n");
       printf("                                                _/        _/    _/                                    \n");
       printf("                                               _/  _/_/  _/     _/                                    \n");
       printf("                                               _/    _/  _/    _/                                      \n");
       printf("                                                _/_/_/    _/ _/                                         \n\n");
}
void affiche_menu1(){//fonction d'affichage du premier menu du jeux
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("          %d /  PLAY              |\n",1);
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n");
    printf("\n");
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("          %d /  RULES             |\n",2);
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n");
    printf("\n");
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf(" |");
    printf("          %d /  EXIT              |\n",3);
    printf("\t\t\t\t\t");
    printf(" |");
    printf("                                 |\n");
    printf("\t\t\t\t\t");
    printf("  ");
    printf(" -------------------------------\n\n");
}
void affiche_menu2(){//fonction d'affichage du deuxieme menu
    slogan();
    printf("\t\t\t\t\t");
        printf("  ");
        printf("-------------------------------\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("                                |\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("   %d /  PLAYER  VS  PLAYER      |\n",1);
        printf("\t\t\t\t\t");
        printf("  ");
        printf("-------------------------------\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("                                |\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("   %d /  PLAYER VS MACHINE       |\n",2);
        printf("\t\t\t\t\t");
        printf("  ");
        printf("-------------------------------\n");
        printf("\t\t\t\t\t");
        printf("  ");
        printf("-------------------------------\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("                                |\n");
        printf("\t\t\t\t\t");
        printf("|");
        printf("   %d / MACHINE INTELLIGENTE     |\n",3);
        printf("\t\t\t\t\t");
        printf("  ");
        printf("-------------------------------\n");
}
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);

}
void colorplayer(int p){//fonction d'affichage des carres colores en fonction du joueur
   if(p==1){
   Color(15,15);
   printf("**");
   Color(15, 0);
   printf("");
   }
   if(p==2){
      Color(11,11);
      printf("**");
      Color(15, 0);
      printf("");
   }
}
void take_position(stone goban[81],int player,int position,int *tab1,int *tab2){/*c'est la fonction principlae de notre jeux
                                                                                qui permet a un joueur de prendre son coup
                                                                                et qui ressemble les regles de notre jeux*/
   if(player==1){
        Color(15,0);
        printf("\t\t\t\tIF YOU WANT TO EXIT TAP 0\n\n");
        printf("\t\t\t\t\t Enter please a position in the goban >>>\t");
        scanf("%d",&position);
        if(position==0){
            FIN=0;
            return;
        }
    }
    if(player==2){
        Color(11,0);
        printf("\t\t\t\tIF YOU WANT TO EXIT TAP 0\n\n");
        printf("\t\t\t\t\t Enter please a position in the goban >>>\t");
        scanf("%d",&position);
        if(position==0){
            FIN=0;
            return;
        }
    }
    if(position>=1 && position<=81){
        if(goban[position-1].color==0){
                if(player==1){
                     goban[position-1].color=1;
                     save(goban,tab1);
                     tremove2(goban,position);
                     if(ko_check(tab2,tab1)==1){
                        Color(12,0);
                        printf("\t\t\t attention ko (....)");
                        take_position(goban,1,position,tab1,tab2);
                     }
                      if(suicide_regle(goban,position)==1){
                        printf("\n\n\t\t\t attention suicide!! try again");
                        goban[position-1].color=0;
                        take_position(goban,1,position,tab1,tab2);
                      }
                     capture_chaine(goban,2,position);
                     system("@cls||clear");
                     show(goban,score1,score2);

                }else{
                    goban[position-1].color=2;
                    save(goban,tab2);
                     tremove2(goban,position);
                     if(ko_check(tab2,tab1)==1){
                        printf("\n\n\t\t\t attention ko (..)");
                        take_position(goban,2,position,tab1,tab2);
                     }
                    if(suicide_regle(goban,position)==1){
                        printf("\n\n\t\t\t attention suicide!! try again");
                        goban[position-1].color=0;
                        take_position(goban,2,position,tab1,tab2);
                    }
                    capture_chaine(goban,1,position);
                    system("@cls||clear");
                    show(goban,score1,score2);
               }
       }else{
            Color(3,0);
            printf("\n\n\t\t\t already filled try again (..)");
            take_position(goban,player,position,tab1,tab2);
       }
    }else{
        Color(6,0);
        printf("\n\n\t\t\t You are giving a position that is not in the goban!!!");
        take_position(goban,player,position,tab1,tab2);
    }
}
int above_position(int position){//fonction qui retourne la position haute si elle existe d'une position donnee 0 sinon
    if(position<=8)
        return 0;
    else
        return (position-9);
}
int under_position(int position){//fonction qui retourne la position basse si elle existe d'une position donnee 0 sinon
    if(position>72)
        return 0;
    else
        return (position+9);
}
int left_position(int position){//fonction qui retourne la position gauche si elle existe d'une position donnee 0 sinon
    if((position-1)%9==0)
        return 0;
    else
        return (position-1);
}
int right_position(int position){//fonction qui retourne la position droite si elle existe d'une position donnee 0 sinon
    if(position%9==0)
        return 0;
    else
        return (position+1);
}
int number_of_liberties(stone goban[81],int position){//fonction qui retourne le nombre de liberte pour une position donnee
    int lib=0;
    if(above_position(position)!=0){
        if(goban[above_position(position)-1].color==0){
            lib++;
        }
    }
    if(under_position(position)!=0){
        if(goban[under_position(position)-1].color==0){
            lib++;
        }
    }
    if(left_position(position)!=0){
        if(goban[left_position(position)-1].color==0){
            lib++;
        }
    }
    if(right_position(position)!=0){
        if(goban[right_position(position)-1].color==0){
            lib++;
        }
    }
    return lib;
}
int * tab_liberties(stone goban[81],int position){/*fonction qui retourne pour une position donnee un tableau qui contient
                                                    les positions des libertees*/
            int *tab=(int *)calloc(4,sizeof(int));
            int j=0;
            if(under_position(position)!=0){
                if(goban[under_position(position)-1].color==0){
                    tab[j]=under_position(position);
                    j++;
            }}
            if(above_position(position)!=0 ){
            if(goban[above_position(position)-1].color==0){
                    tab[j]=above_position(position);
                    j++;
            }}
            if(right_position(position)!=0 ){
            if(goban[right_position(position)-1].color==0){
                    tab[j]=right_position(position);
                    j++;
            }}
            if(left_position(position)!=0){
            if(goban[left_position(position)-1].color==0){
                    tab[j]=left_position(position);
                    j++;
            }}

    return tab;
}
int enemy(stone goban[81],int position){/*fonction retourne pour une position le nombre de pierres adjacentes qui ont une couleur
                                        adverse de la couleur de la position en question*/
    int n=0;
    if(under_position(position)!=0 && goban[under_position(position)-1].color!=0){
         if(goban[position-1].color!=goban[under_position(position)-1].color){
                    n++;
         }
    }
    if(above_position(position)!=0 && goban[above_position(position)-1].color!=0){
         if(goban[position-1].color!=goban[above_position(position)-1].color){
            n++;
         }
    }
    if(left_position(position)!=0 && goban[left_position(position)-1].color!=0){
         if(goban[position-1].color!=goban[left_position(position)-1].color){
                   n++;
         }
    }
    if(right_position(position)!=0 && goban[right_position(position)-1].color!=0){
         if(goban[position-1].color!=goban[right_position(position)-1].color){
                       n++;
         }
    }
    return n;
}
int numbers_voisin(stone goban[81],int position){/*fonction qui retourne pour une position donnee le nombre d'intersections
                                                  adjacentes possibles pour cette position*/
    int voisin=0;
    if(above_position(position)!=0){
            voisin++;
    }
    if(under_position(position)!=0){
            voisin++;
        }
    if(left_position(position)!=0){
        voisin++;
    }
    if(right_position(position)!=0){
       voisin++;
    }
    return voisin;
}
int ami(stone goban[81],int position){/*fonction qui retourne le nombre de pierres adjacentes qui ont la meme couleur que
                                        la position en question*/
    int ami=0;
    if(under_position(position)!=0 && goban[under_position(position)-1].color!=0){
         if(goban[position-1].color==goban[under_position(position)-1].color){
                    ami++;
         }
    }
    if(above_position(position)!=0 && goban[above_position(position)-1].color!=0){
         if(goban[position-1].color==goban[above_position(position)-1].color){
            ami++;
         }
    }
    if(left_position(position)!=0 && goban[left_position(position)-1].color!=0){
         if(goban[position-1].color==goban[left_position(position)-1].color){
                   ami++;
         }
    }
    if(right_position(position)!=0 && goban[right_position(position)-1].color!=0){
         if(goban[position-1].color==goban[right_position(position)-1].color){
                       ami++;
         }
    }
    return ami;
}

int * tabami(stone goban[81],int position){/*fonction qui retourne les positions  de pierres adjacentes qui ont la meme couleur que
                                        la position en question*/
            int *tab=(int *)calloc(5,sizeof(int));
            int j=0;
            tab[j]=position;
            j++;
            if(under_position(position)!=0){
                if(goban[position-1].color==goban[under_position(position)-1].color){
                    tab[j]=under_position(position);
                    j++;
            }}
            if(above_position(position)!=0 ){
            if(goban[position-1].color==goban[above_position(position)-1].color){
                    tab[j]=above_position(position);
                    j++;
            }}
            if(right_position(position)!=0 ){
            if(goban[position-1].color==goban[right_position(position)-1].color){
                    tab[j]=right_position(position);
                    j++;
            }}
            if(left_position(position)!=0){
            if(goban[position-1].color==goban[left_position(position)-1].color){
                    tab[j]=left_position(position);
                    j++;
            }}

    return tab;
}
int in_table(int *tab,int position){ //fonction qui retourne 1 si la position en question est dans la table sinon elle retourne 0
    for(int i=0;i<80;i++){
        if(tab[i]==position)
            return 1;
    }
    return 0;
}
void identifier_groupe(stone goban[81],int position,int *tab_positions_chaine){
    int *tab_amis_pour_une_position=tabami(goban,position);
    for(int i=0;i<5;i++){
        if(tab_amis_pour_une_position[i]!=0 && in_table(tab_positions_chaine,tab_amis_pour_une_position[i])==0){
        tab_positions_chaine[M]=tab_amis_pour_une_position[i];
        M++;
        chaine_complete(goban,tab_amis_pour_une_position[i],tab_positions_chaine);
    }
}
}
void chaine_complete(stone goban[81],int position,int *tab_positions_chaine){/*fonction qui est en collaboration avec la fonction identifier_groupe permet
                                                                              a partir de la position en question de determiner  toute les positions la
                                                                            chaine d'ou elle appartient et de les stockers dans le tableau en parametres */

                int *tab1=tabami(goban,position);
                for(int k=0;k<5;k++){
                identifier_groupe(goban,tab1[k],tab_positions_chaine);
                int *tab2=tabami(goban,tab1[k]);
                for(int e=0;e<5;e++){
                identifier_groupe(goban,tab2[e],tab_positions_chaine);
                int *tab3=tabami(goban,tab2[e]);
                for(int r=0;r<5;r++){
                identifier_groupe(goban,tab3[r],tab_positions_chaine);
                }}}}


int *chaine_liberties(stone goban[81],int *tab_positions_chaine){/*fonction qui retourne un tableau des positions de libertes pour une chaine
                                                                    dont les positions sont stockees dans le tableau en parametres*/
    int *positions_of_liberties_chaine=(int *)calloc(80,sizeof(int));
    int k=0;
    for(int i=0;i<80;i++){
        if(tab_positions_chaine[i]>=1 && tab_positions_chaine[i]<=81){
        int *tab_libertie_element=tab_liberties(goban,tab_positions_chaine[i]);
        for(int j=0;j<4;j++){
            if(tab_libertie_element[j]!=0 && in_table(positions_of_liberties_chaine,tab_libertie_element[j])==0){
                    positions_of_liberties_chaine[k]=tab_libertie_element[j];
                    k++;
          }
        }
      }
    }
    return positions_of_liberties_chaine;
}
int numbers_liberties_chaine(stone goban[81],int *tab){/*fonction qui donne le nombre de liberte effectif dans la table des positions de libertesn
                                                       d'une chaine (tab) a cause de calloc */
    int liber=0;
    for(int i=0;i<80;i++){
        if(tab[i]>=1 && tab[i]<=81){
                liber++;
        }
    }
    return liber++;
}
void  capture_chaine(stone goban[81],int player,int position){//fonction qui permet de capturer une chaine de l'adversaire(player)

   int *tab_enem=tab_enemy(goban,position);
   for(int j=0;j<4;j++){
    if(tab_enem[j]!=0){
            if(ami(goban,tab_enem[j])!=0){
                int *tab=(int *)calloc(80,sizeof(int));
                chaine_complete(goban,tab_enem[j],tab);
                int *chaine_li=chaine_liberties(goban,tab);
                if(numbers_liberties_chaine(goban,chaine_li)==0){
                    remove_chaine(goban,tab);
                }
            }
       }
    }
}
int  suicide_regle(stone goban[81],int position){//fonction qui retourne 1 s'il y a le cas de suicide pour la position en question
   if(ami(goban,position)!=0){
        int *tab=(int *)calloc(80,sizeof(int));
        chaine_complete(goban,position,tab);
        int *chaine_li=chaine_liberties(goban,tab);
        if(numbers_liberties_chaine(goban,chaine_li)==0){
           return 1;
        }else{
            return 0;
        }
   }else{
       if(number_of_liberties(goban,position)==0 && numbers_voisin(goban,position)==enemy(goban,position)){
            return 1;
       }else{
           return 0;
       }
   }
}

void machine_joueur(stone goban[81]){//fonction pour joueur VS machine
    int position;
    int player1, player2;
    srand(time(NULL));
    player1 = rand() % 2 + 1;
    player2 = 3 - player1;
    slogan();
    show(goban,score1,score2);
    printf("\t\t\t the player who will play first is >>>>\t%d\n\n", player1);
    while (FIN==1) {
        int *tab1=(int *)calloc(81,sizeof(int ));
        int *tab2=(int *)calloc(81,sizeof(int ));
        if (player1 == 1) {
            take_position(goban, player1, position,tab1,tab2);
        }else{
            // Comput's turn
            int ai_position = rand()% 81 + 1;
            again:if (goban[ai_position - 1].color == 0) {
                goban[ai_position - 1].color = player1;
            } else {
                // Try again until an empty position is found
                while (goban[ai_position - 1].color != 0) {
                    ai_position = rand() % 81 + 1;
                }
                goban[ai_position - 1].color = player1;
                save(goban,tab2);
                tremove2(goban,ai_position);
                if(ko_check(tab2,tab1)==1){
                    goto again;
                }
                if(suicide_regle(goban,ai_position)==1){
                        goban[position-1].color=0;
                        goto again;
                }
                capture_chaine(goban,1,ai_position);
                system("@cls||clear");
                show(goban,score1,score2);
            }
        }
        take_position(goban, player2, position,tab1,tab2);
    }
    if(score1<score2){
       Color(7,0);
       printf("\n\t\t\tLa machine te gagne elle est assez puissante n\'est ce pas ");
    }else{
        Color(6,0);
        printf("\n\t\t\t Tu as gagner");
    }
}
void machine_intelligente(stone goban[81]){//fonction pour jouer contre machine intelligente
    int position;
    srand(time(NULL));
    slogan();
    show(goban,score1,score2);
    while (FIN==1){ //tant que le joueur ne desire pas de quitter le jeu
        int *tab1=(int *)calloc(81,sizeof(int ));
        int *tab2=(int *)calloc(81,sizeof(int ));
        take_position(goban,1, position,tab1,tab2);
        int attaque_pos=attaque(goban,1);
        save(goban,tab2);
        tremove2(goban,attaque_pos);
        capture_chaine(goban,1,attaque_pos);
        system("@cls||clear");
        show(goban,score1,score2);
        //defence(goban,1);
    }
    if(score1<score2){
       Color(7,0);
       printf("\n\t\t\tLa machine te gagne elle est assez puissante n\'est ce pas ");
    }else{
        Color(6,0);
        printf("\n\t\t\t Tu as gagner");
    }
}

int ko_check(int *tab1,int *tab2){//fonction qui retourne 1 si les deux tableaux sont egaux 0 sinon
    int r=0;
    for(int i=0;i<81;i++){
        if(tab1[i]==tab2[i])
            r++;
    }
    if(r==81)
        return 1;
    return 0;
}
void save(stone goban[81],int *tab){//fonction qui conserve l'etat du goban(couleur) dans le tableau en parametre
    for(int i=0;i<81;i++){
        tab[i]=goban[i].color;
    }
}
int *tab_voisins(stone goban[81],int position){//fonction qui retourne le tableau des positions des intersections adjcentes a la position en question
    int *tab=(int *)calloc(4,sizeof(int));
    int i=0;
    if(under_position(position)!=0){
        tab[i]=under_position(position);
        i++;
    }
    if(above_position(position)!=0){
        tab[i]=above_position(position);
        i++;
    }
    if(left_position(position)!=0){
        tab[i]=under_position(position);
        i++;
    }
    if(right_position(position)!=0){
        tab[i]=right_position(position);
        i++;
    }
}
int *tab_enemy(stone goban[81],int position){/*fonction qui retourne le tableau des positions des intersections adjcentes
                                               qui ont la couleur adverse de la couleur de la position en question*/
    int *tab=(int *)calloc(4,sizeof(int));
    int i=0;
    if(under_position(position)!=0 && goban[under_position(position)-1].color!=0 &&  goban[under_position(position)-1].color!=goban[position-1].color){
        tab[i]=under_position(position);
        i++;
    }
    if(above_position(position)!=0 && goban[above_position(position)-1].color!=0 &&  goban[above_position(position)-1].color!=goban[position-1].color){
        tab[i]=above_position(position);
        i++;
    }
    if(right_position(position)!=0 && goban[right_position(position)-1].color!=0 &&  goban[right_position(position)-1].color!=goban[position-1].color){
        tab[i]=right_position(position);
        i++;
    }
    if(left_position(position)!=0 && goban[left_position(position)-1].color!=0 &&  goban[left_position(position)-1].color!=goban[position-1].color){
        tab[i]=left_position(position);
        i++;
    }
    return tab;
}
void tremove2(stone goban[81],int position){//fonction qui permet de capturer une pierres adverses
    int *tab=tab_enemy(goban,position);
    int inter;
    for(int i=0;i<4;i++){
        if(tab[i]!=0 && enemy(goban,tab[i])==numbers_voisin(goban,tab[i])){
            inter=goban[tab[i]-1].color;
            goban[tab[i]-1].color=0;
            if(inter==1)
                score2++;
            score1++;
        }
    }
}

void rules_of_GO(){//fonction d'affichage de regles du jeux
    printf("1_|Les joueurs placent tour a tour une pierre de leur couleur sur le plateau, sur un point d\'intersection vide.\n\n");
    printf("2_|Une pierre ou un groupe de pierres de meme couleur est capture et retire du plateau lorsqu\'il est completement entoure par les pierres de l\'adversaire.\n\n");
    printf("3_|Les pierres ne peuvent etre deplacees qu\'en les capturant.\n\n");
    printf("4_|Une pierre ne peut pas etre placee sur un point d'intersection si cela aboutirait a sa capture immediate.\n\n");
    printf("5_|Le but du jeu est de controler le plus grand territoire possible sur le plateau, en utilisant vos pierres pour encercler les zones vides.\n\n");
    printf("6_|Le jeu se termine lorsque les deux joueurs passent consecutivement leur tour, ou lorsqu\'il n\'y a plus de points d'intersection vides sur le plateau.\n\n");
    printf("7_|Le joueur qui controle le plus grand territoire a la fin de la partie remporte la partie.\n\n");
}
void remove_chaine(stone goban[81],int *tab_positions){//fonction de capture de chaine
    for(int j=0;j<80;j++){
        if(tab_positions[j]!=0){
            int inter=goban[tab_positions[j]-1].color;
            goban[tab_positions[j]-1].color=0;
            if(inter==1){
                score2++;
            }else{
             score1++;
            }
        }
    }
}
int  attaque(stone goban[81],int player1){/*fonction pour la machine pour attaquer le joueur qui retourne la position
                                             ou la machine doit jouer pour gagner*/
    if(est_vide==1){ //si le goban est vide
            int first_position=rand()%81+1; //position aleatoire
            goban[first_position-1].color=3-player1;//la machine joue a la place du 2e joueur
    }else{
        for(int i=0;i<81;i++){
         if(goban[i].color!=0 && goban[i].color==player1){//si la case est remplie par le joueur
            if(number_of_liberties(goban,i+1)==1){
                int *tab=tab_liberties(goban,i+1);
                for(int j=0;j<4;j++){
                    if(goban[tab[j]-1].color==0){
                        goban[tab[j]-1].color=3-player1;
                        return tab[j];
                        break;
                    }
                }
            }else{
                int *tab2=tab_liberties(goban,i+1);
                for(int e=0;e<4;e++){
                    if(tab2[e]!=0 && goban[tab2[e]-1].color==0){
                        goban[tab2[e]-1].color=3-player1;
                        return tab2[e];
                        break;
                }
            }
        }
      }
}
}}
int est_vide(stone goban[81]){//fonction retourne 1 si le goban est vide 0 sinon
    int compteur=0;
    for(int i=0;i<81;i++){
        if(goban[i].color==0)
            compteur++;
    }
    if(compteur==81){
        return 1;
    }
    return 0;
}
void defence(stone goban[81],int player){
    if(est_vide==0){//si le goban n'est pas vide
    for(int i=0;i<81;i++){
        if(goban[i].color!=0 && goban[i].color!=player){
            int n=number_of_liberties(goban,i+1);
            if(enemy(goban,i+1)==n-1){
                int *tab=tab_voisins(goban,i+1);
                for(int i=0;i<4;i++){
                    if(goban[tab[i]-1].color==0){
                        goban[tab[i]-1].color=(3-player);
                    }
                }
            }
        }
    }
    }
}
int number_of_stones_exist_in_the_goban(stone goban[81],int player){/*fonction qui prend en parametres le goban et un joueur et qui retourne
                                                                    le nombre de pierres de ce joueur dans le goban*/
    int stones=0;
    for(int i=0;i<81;i++){
        if(goban[i].color==player)
            stones++;
    }
    return stones;
}
