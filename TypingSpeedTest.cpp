#include <fstream.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <iomanip.h>

int wordsPerLine = 5;

struct score
{
 char name[80];
 int score;

 score()
 {
  score = -1;
 }
};

void main()
{
 clrscr();

 int option = -1;

 //ofstream highout("highscore.txt", ios::trunc);

 do
 {
  cout << "Enter 1 to see the  highscores, or 2 to take the test.\n";
  cout << "Enter anything else to quit.\n";
  cin >> option;
  //cout << option;
  if(option == 1)
  {
   ifstream highin("high.txt");
   //cout << '|' << option << '\n';
   score sc;

   while(!highin.eof())
   {
    highin >> sc.name >> sc.score;
    if(highin.eof()) break;
    for(int j = 0; sc.name[j] != '\0'; j++)
    {
     if(sc.name[j] == '_') cout << ' ';
     else cout << sc.name[j];
    }
    cout << '\t' << sc.score << '\n';
   }

   /*int x;
   highin >> x;
   cout << x << '\n';*/

   //cout << "=========\n";
  }
  if(option == 2)
  {
   ifstream highin("high.txt");
   int maxWords;

   clrscr();
   randomize();

   ifstream dict("dict.txt");

   char words[256][80];

   for(maxWords = 0; !dict.eof(); maxWords++)
   {
    dict>>words[maxWords];
    //cout << i << ' ' << words[i] << '\n';
   }

   int wordCount = -1;

   cout<<"==Typing Speed Test==\n\n";
   cout<<"Enter number of words (at least 10): ";

   cin>>wordCount;
   while(wordCount < 10)
   {
    cout<<"Enter a number not less than ten: ";
    cin >> wordCount;
   }

   cout<<"Press space between words. \nPress enter when you're done. \nPress any key to begin.\n";

   cout << '\n';

   getch();

   int wordList[500];
   int used[500];

   for(int i = 0; i < 500; i++)
   {
    used[i] = 0;
   }

   for(i = 0; i < wordCount; i++)
   {
    int r = random(maxWords);

    int j;

    //cout << '\n' << r << ' ';

    for(j = 0; r != -1; j++)
    {
     if(used[j] == 0)
     {
      r--;
     }
    }

    j--;

    //cout << j << ' ';

    used[j] = 1;

    cout << words[j] << ' ';
    wordList[i] = j;

    maxWords--;

    if(i % wordsPerLine == wordsPerLine - 1) cout << '\n';
   } cout << "\n";
   char ans[5000] = "";

   double start_t = clock();

   for(i = 0; i <= (wordCount - 1)/wordsPerLine; i++)
   {
    int len = strlen(ans);
    //cout << '\n' << len << '\n';
    gets(ans + len);
    len = strlen(ans);
    ans[len] = ' ';
   }

   //cout << "\n\n\n" << ans << "\n\n";

   double end_t = clock();

   int curWord = 0, j = 0;
   int correct[1000];

   for(i = 0; i < 200; i++)
   {
    correct[i] = 0;
   }

   for(i = 0; ans[i] != '\0'; i++)
   {
    //cout << i << ' ' << j << ' ' << curWord << ' ' << ans[i] << '\n';
    if(ans[i] == ' ')
    {
     //cout << "END";
     if(words[wordList[curWord]][j] == '\0')
     {
      //cout << "REA";
      correct[curWord] = 1;
      //cout << words[wordList[curWord]][j] << '\n';
     }
     j = -1;
     curWord++;
    }
    else if(ans[i] != words[wordList[curWord]][j])
    {
     correct[curWord] = 0;
     j = -1;

     while(ans[i] != ' ')
     {
      i++;
     }
     curWord++;
    }
    j++;
   }

   //cout << "END";
   /*if(words[wordList[curWord]][j] == '\0')
   {
     //cout << "REA";
     correct[curWord] = 1;
     //cout << words[wordList[curWord]][j] << '\n';
   }*/

   cout << '\n';
   cout << "You typed the following words incorrectly:\n";
   int wrong = 0;
   double charCount = 0;
   for(i = 0; i < wordCount; i++)
   {
    if(correct[i] == 1)
    {
     charCount += strlen(words[wordList[i]]);
    }
    else
    {
     wrong++;
     cout << words[wordList[i]] << ' ';
    }
   }
   if(wrong == 0) cout << "NONE!\n";
   cout << '\n';

   double totTime = (end_t - start_t) / CLK_TCK;

   cout << "\nIn total, you took " << ((float)((int)(totTime*100)))/100.0;
   cout << " seconds. \nYou typed " << (int)((charCount / totTime) * 60.0);
   cout << " characters per minute. ";

   cout << "=========\n";

   score sc[15];

   int cpm = (int)((charCount / totTime) * 60.0);

   int found = 0;

   //HIGHSCORES

   for(i = 0; !highin.eof(); i++)
   {
    highin >> sc[i].name >> sc[i].score;
    if(i == 10) break;
    if(cpm > sc[i].score && found == 0)
    {
     cout << ':' << i << '\n';
     sc[i + 1] = sc[i];
     found = 1;
     cout << "NEW HIGH SCORE! Enter your name: ";
     gets(sc[i].name);
     for(int j = 0; sc[i].name[j] != '\0'; j++)
     {
      if(sc[i].name[j] == ' ') sc[i].name[j] = '_';
     }
     sc[i].score = cpm;
     i++;
    }
   }

   highin.close();
   ofstream highout("high.txt", ios::trunc);

   for(i = 0; i < 10 && sc[i].score != -1; i++)
   {
    highout << sc[i].name << ' ' << sc[i].score << '\n';
   }

   //getch();
   //getch();
  }
 }while(option == 1 || option == 2);
}