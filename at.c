#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


bool executeCommand(char str[100])
{
// printf("executeCommand: %s\n", str);
system(str);
return true;
}

bool readFile(int hour, int min)
{
FILE *fp;
char str[255];
char time[25];
fp = fopen("at.txt","r");

if( fp == NULL )
{
perror("Error while opening the file.\n");
exit(EXIT_FAILURE);
}
 
int t_hour = -1;
int t_min = -1;
int t_sec = -1;

char tmpStr[2];
tmpStr[0] =char(0);
tmpStr[1] =char(0);


int i=0;
int j=0;
int ch;
while( ( ch = fgetc(fp) ) != EOF )
{
  if (ch == char(10)) {
	// printf("command to run: %s\n", str);
	// printf("Time from file: %d:%d\n", t_hour, t_min);
	
	if ((t_hour==hour) && (t_min == min))
		executeCommand(str);

	j=0;
	tmpStr[0] =char(0);
	tmpStr[1] =char(0);
	i=0;

	t_hour = -1;
	t_min = -1;
	t_sec = -1;

	for (int x=0;x<255;x++)
		str[x]=char(0);
  } else {

	if ((t_hour == -1) && (ch != char(58)))
	{
		tmpStr[j] = ch;
		j++;
	} 
	else 
	{

	if ((t_hour == -1) && (ch == char(58)))
	{
		if (tmpStr[1] == char(0))
			t_hour = (int)tmpStr[0] - '0';
		else 
			t_hour = atoi(tmpStr);
		j=0;
		tmpStr[0] =char(0);
		tmpStr[1] =char(0);
	} 
	else  
	{
	
	if ((t_hour > -1) && (t_min == -1) && (ch != char(58)))
	{
		tmpStr[j] = ch;
		j++;
	} 
	else 
	{
	if ((j>0) && (t_hour > -1) && (t_min == -1) && (ch == char(58)))
	{
		// printf("STRING %s\n", tmpStr);
		if (tmpStr[1] == char(0)) {
			t_min = (int)tmpStr[0] - '0';
		}
		else { 
			t_min = atoi(tmpStr);
		}
		tmpStr[0] =char(0);
		tmpStr[1] =char(0);
		j=0;
	} else 
	{

	// printf("MIN %d", t_min);
	/*
	if ((t_hour > -1) &&  (t_min > -1) && (t_sec == -1) && (ch != char(58)))
	{
		tmpStr[j] = ch;
		j++;
	}

	if ((j>0) && (t_hour > -1) &&  (t_min > -1) && (t_sec == -1) && (ch == char(58)))
	{
		// printf("STRING %s", tmpStr);
		t_sec = atoi(tmpStr);
		tmpStr[0] =char(0);
		tmpStr[1] =char(0);
		j=0;
	}
	*/
		str[i] = ch;
  		i++;
	}
	}
	}
	}
  }
}

 
fclose(fp);
return true;

}

int main(int argc, char** argv)
{
time_t rawtime;
struct tm * timeinfo;


int slp = atoi(argv[1]);

if (slp <= 0)
	slp = 600;

// printf("Sleep time is: %d \n", slp);

for (;;)
{
time ( &rawtime );
timeinfo = localtime ( &rawtime );
// printf("TIME\n  %d-%d-%d %d:%d:%d \n", timeinfo->tm_year + 1900 , timeinfo->tm_mon + 1 , timeinfo->tm_mday , 
//		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
readFile(timeinfo->tm_hour, timeinfo->tm_min);
sleep(slp);
}


return 0;
}
