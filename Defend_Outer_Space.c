/* To do list:
-2d Array containing enemies, player, and lasers.
-Player can only move left and right via letters A and D.
-Player will shoot via 'm'.
-Print Start screen and explain rules.
-When all enemies die, print score and win screen.
-When player dies print game over and score screen.
*/

//Toolboxes Required
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> //rand(), srand(), atexit()
#include <time.h>   //time()
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

//Forward Declaration of functions
int Game();
void enableRaw();
void disableRaw();
void print();
void enemylasers();
void playerlaser();

//Declaration of Global Variables
struct termios orig_termios;
int i=0, j=0, Xaxis=47, Yaxis=47, totalenemies=472, score=0, life=3;
int playerX=23, playerY=44, laserX, laserY, difficulty;
float frequent;
char player;
char enemy1='M', enemy2='U', enemy3='H', explosion='X';
char laser='.', direction='r', enemylaser='I';
char field[47][47] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', ' ', ' '},
    {' ', ' ', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', ' ', ' '},
    {' ', ' ', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', ' ', ' '},
    {' ', ' ', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', 'M', ' ', ' ', ' '},
    {' ', ' ', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' '},
    {' ', ' ', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' '},
    {' ', ' ', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' '},
    {' ', ' ', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' '},
    {' ', ' ', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', 'H', 'H', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

//Main Function: Where the magic happens
int main() {

    int k, l, m, n;
    char move, junk;

    //Prints out start screen and custom options
    system("clear");
    printf("   *                     *                            *                         *                         *                                       *                            *\n  *       *            *                  *                    *                                   *                   *                        *                                  \n*  "
        "                 *                *             *                                                                          *                               *                \n     *                     *           *      *                        *            *                  *                   *                        *                     \n*                *   "
        "           *                    *                           *      *                                        *                   *                         \n*               *                          *                            *                         *                       *                             *                       \n                 *               "
        "       *                           *                       *                          *                    *               *                 \n*        *           *                     *                                                                 *                                      *                *               \n     *                   *               "
        "               *                                          *                 *                                   *                 \n*        *        *        *    *                                       *          *      *                                                     *         *                 \n     *                               *              *        "
        "                 *                               *                                      *         *                 \n    *                        *    *                     *                                *                  *                 *                          *                 \n                                      *              *     *                "
        "                  *                  *                                        *                        \n\tWelcome to Starbase 150, Captain. Your mission is to save the earth from the invading horde.\n\tBefore you head out, I need to know which ship you would like.\n\n\n\n\n\n\n\n\t");
    printf("\n\n\n\tHere are the flight controls for all of our spaceships:\n\n\t\'a\' to move left\n\t\'d\' to move right\n\t\'m\' to shoot lasers\n\t\n\n\n\n\n\n\n\tHere are our available spaceships\n\n\tV\tA\tY\tT\t^\t*\n\n\n\n\tPlease select a spaceship: ");
    scanf(" %c", &player);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n   *                     *                            *                         *                         *                                       *                            *\n  *       *            *                  *                    *                                   *                   *                        * "
        "                                 \n*                   *                *             *                                                                          *                               *                \n     *                     *           *      *                        *            *                  *                   *                        *      "
        "               \n*                *              *                    *                           *      *                                        *                   *                         \n*               *                          *                            *                         *                       *                             *                    "
        "   \n                 *                      *                           *                       *                          *                    *               *                 \n*        *           *                     *                                                                 *                                      *                *               \n   "
        "  *                   *                              *                                          *                 *                                   *                 \n*        *        *        *    *                                       *          *      *                                                     *         *                 \n     *                 "
        "              *              *                         *                               *                                      *         *                 \n    *                        *    *                     *                                *                  *                 *                          *                 \n                                      "
        "*              *     *                                  *                  *                                        *                        \n\n\n\n\n\n\n\n\n\t");
    printf("\n\tEnter your difficulty: \n\n\t1-In the rear (Easy) \n\n\t2-On the frontlines (Normal) \n\n\t3-Behind enemy lines (Impossible)\n\n\n\n\n\n\n\n   *                     *                            *                         *                         *                                       *                            *\n  *       *            *                "
        "  *                    *                                   *                   *                        *                                  \n*                   *                *             *                                                                          *                               *                \n     *                     *           *      *  "
        "                      *            *                  *                   *                        *                     \n*                *              *                    *                           *      *                                        *                   *                         \n*               *                          *                       "
        "     *                         *                       *                             *                       \n                 *                      *                           *                       *                          *                    *               *                 \n*        *           *                     *                                    "
        "                             *                                      *                *               \n     *                   *                              *                                          *                 *                                   *                 \n*        *        *        *    *                                       *          *      *"
        "                                                     *         *                 \n     *                               *              *                         *                               *                                      *         *                 \n    *                        *    *                     *                                *               "
        "   *                 *                          *                 \n                                      *              *     *                                  *                  *                                        *                        \n");
    scanf("%d", &difficulty);
    enableRaw();
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    Game();

    //Runs the actual gameplay scenario
   while(move!='x' && life!=0 && totalenemies>0) {
       usleep(100000);
       read(STDIN_FILENO, &move, 1);
       system("clear");
       Game();
       //Moves lasers upwards and adds to score when enemy is hit
       for(i=1; i<46; i++) {
           for(j=1; j<46; j++) {
               if(field[i][j]==laser) {
                   field[i][j]=' ';
                   if(field[i-1][j]==' ') {
                       field[i-1][j]=laser;
                   } else if(field[i-1][j]==enemy1 || field[i-1][j]==enemy2 || field[i-1][j]==enemy3) {
                       field[i-1][j]=explosion;
                       field[i][j]=' ';
                       score+=50;
                   }
               } else if(field[i][j]==explosion) {
                   field[i][j]=' ';
               }
           }
       }
       //Moves enemy lasers down and explodes when hit with player laser
       for(i=46; i>1; i--) {
           for(j=46; j>1; j--) {
               if(field[i][j]==enemylaser) {
                   if(i<46 && field[i][j+1]==player) {
                   } else if(i<46 && field[i+1][j]==' ') {
                       field[i][j]=' ';
                       field[i+1][j]=enemylaser;
                   } else if(i<46 && field[i+1][j]==laser) {
                       field[i][j]=' ';
                       field[i+1][j]=explosion;
                   }
                   field[i][j]=' ';
               }
           }
       }
       //Prevents enemy laser buildup at bottom of gameboard
       for(k=1; k<47; k++) {
           for(l=1; l<47; l++) {
               if(k>=46 && k<=47 && field[k][l]==enemylaser) {
                   field[k][l]=' ';
               }
           }
       }
       //Takes life away from player when player is hit with laser
       for(m=0; m<46; m++) {
           for(n=0; n<46; n++) {
               if(field[playerY][playerX]==enemylaser) {
                   frequent=-0.5;
               }
           }
       }
       //takes away life and resets frequent to 0
       life+=frequent;
       frequent=0;
       //Displays score, enemies remaining, and lives left
       print();
       //Allows player movement and laser control
       if(move=='a' && playerX>1 ) {
           playerX--;
       } else if(move=='d' && playerX<46) {
           playerX++;
       } else if(move=='m' && playerX<45) {
           playerlaser();
       }
   }
   //Takes console out of raw mode and puts it back into canonical mode
   disableRaw();
   return 0;
}

//Create game board
int Game() {

   char border = '*';

   //Places player on board and prints border
   for(i=0; i<48; i++) {
       for(j=0; j<48; j++) {
           if(i == playerY && j == playerX) {
               printf("%2c", player);
           } else if(j == 0 || j == 47 || i == 0 || i == 47) {
               printf("%2c", border);
           } else {
               printf("%2c", field[i][j]);
           }
           //Populates enemy lasers
           enemylasers();
       }
       printf("\n");
   }
   printf("Score: %d\t\t\tEnemies Remaining: %d\t\t\t\t Lives: %d\n", score, totalenemies, life);
}

//Declares player's laser coordinates relative to the player
void playerlaser() {

   char explosion = 'X';

   laserX=playerY-1;
   laserY=playerX;
   field[laserX][laserY]=laser;

}

//Turns input into raw mode
void enableRaw() {

   struct termios raw;

   tcgetattr(STDIN_FILENO, &orig_termios);
   atexit(disableRaw);

   raw = orig_termios;
   raw.c_lflag &= ~(ECHO | ICANON);

   tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

}

//Turns input back to canonical mode
void disableRaw() {

   tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

}

//Print enemies remaining
void print() {

   totalenemies=0;

   for(i=0; i<48; i++) {
       for(j=0; j<48; j++) {
           //Counts all of enemy1 and adds to the total
           if(field[i][j]==enemy1) {
               totalenemies=totalenemies+1;
           //Counts all of enemy2
           } else if(field[i][j]==enemy2) {
               totalenemies=totalenemies+1;
           //Counts all of enemy3
           } else if(field[i][j]==enemy3) {
               totalenemies=totalenemies+1;
           }
       }
    }
}

//Randomly generate enemy lasers
void enemylasers() {

   int frequency;

   if(difficulty==1) {
       frequency=(rand()%1000)>996;
       if(totalenemies>350) {
           bool clearance = i <= 42 && field[i][j]==enemy3 && field[i+2][j]!=enemy3 && field[i+4][j]!=enemy3;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>175 && totalenemies<350) {
           bool clearance = i <= 42 && field[i][j]==enemy2 && field[i+2][j]!=enemy2 && field[i+4][j]!=enemy2;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>0 && totalenemies<175) {
           bool clearance = i <= 42 && field[i][j]==enemy1 && field[i+2][j]!=enemy1 && field[i+4][j]!=enemy1;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       }
   } else if(difficulty==2) {
       frequency=(rand()%1000)>994;
       if(totalenemies>350) {
           bool clearance = i <= 42 && field[i][j]==enemy3 && field[i+2][j]!=enemy3 && field[i+4][j]!=enemy3;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>175 && totalenemies<350) {
           bool clearance = i <= 42 && field[i][j]==enemy2 && field[i+2][j]!=enemy2 && field[i+4][j]!=enemy2;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>0 && totalenemies<175) {
           bool clearance = i <= 42 && field[i][j]==enemy1 && field[i+2][j]!=enemy1 && field[i+4][j]!=enemy1;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       }
   } else if(difficulty==3) {
       frequency==(rand()%100)>90;
       if(totalenemies>350) {
           bool clearance = i <= 42 && field[i][j]==enemy3 && field[i+2][j]!=enemy3 && field[i+4][j]!=enemy3;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>175 && totalenemies<350) {
           bool clearance = i <= 42 && field[i][j]==enemy2 && field[i+2][j]!=enemy2 && field[i+4][j]!=enemy2;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       } else if(totalenemies>0 && totalenemies<175) {
           bool clearance = i <= 42 && field[i][j]==enemy1 && field[i+2][j]!=enemy1 && field[i+4][j]!=enemy1;
           if(frequency && clearance && field[i+1][j]!=enemylaser) {
               field[i+1][j]=enemylaser;
           }
       }
    }
}
