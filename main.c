#include<stdio.h>

#include<stdbool.h>

#include<string.h>

#include<stdlib.h>

#include<errno.h>

#include<unistd.h>

#include<sys/shm.h>

#include<sys/types.h>

#include<sys/wait.h>

#include<stdio.h>
#include<string.h>
#include<math.h>

int n;

bool
isSafe (int x, int y)
{

  if (x < 0 || x >= n || y < 0 || y >= n)

    return false;

  else

    return true;

}

int
main1 ()
{
  char s[75];
  char const *const fileName = "input.txt";
  FILE *file = fopen (fileName, "r");
  char line[256];

  fgets (line, sizeof (line), file);
  n = atoi (line);
  fgets (line, sizeof (line), file);
  strcpy (s, line);
  fclose (file);
  n++;

  int x = n - 1, y = 0;

  int matrix[20][20];

  /*
     5 * * * * * *

     4 * * * * * *

     3 * * * * * *

     2 * * * * * *

     1 * * * * * *

     0 * * * * * *

     0 1 2 3 4 5

   */

  int number = 0;

  for (int i = n - 1; i >= 0; i--)

    {

      for (int j = 0; j < n; j++)

	matrix[i][j] = number++;

    }

  int shmid;
  bool *shmflag;
  if ((shmid = shmget (2041, 32, 0666 | IPC_CREAT)) == -1)
    {
      exit (1);
    }
  shmflag = shmat (shmid, 0, 0);
  if (shmflag == (bool *) - 1)
    {
      exit (0);
    }
  shmflag[0] = false;

  int a[500], count = 0;

  a[count] = matrix[n - 1][0];

  FILE *fptr = fopen ("2019B5A71106H_t1.txt", "w");
  count++;
  fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
  fprintf (fptr, "Exploring Path: ");

  for (int i = 0; i < count; i++)

    fprintf (fptr, "%d ", a[i]);

  fprintf (fptr, "\n");
  int len = strlen (s);

  for (int l = 0; l < len; l++)

    {

      if (s[l] == '1')

	{

	  if (isSafe (x - 1, y) && isSafe (x + 1, y))

	    {

	      int p = fork ();

	      if (p == 0)

		{
		  if (shmflag[0] == false)
		    {

		      x = x - 1;

		      y = y;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}

		    }		//wait(NULL);

		}

	      else

		{
		  if (shmflag[0] == false)
		    {
		      wait (NULL);

		      x = x + 1;

		      y = y;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		}



	    }

	  else

	    {

	      if (isSafe (x - 1, y))

		{
		  if (shmflag[0] == false)
		    {
		      x = x - 1;

		      y = y;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		}

	      else

		{
		  if (shmflag[0] == false)
		    {
		      x = x + 1;

		      y = y;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;
			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		}

	    }

	}

      else

	{

	  if (isSafe (x, y - 1) && isSafe (x, y + 1))

	    {

	      int r = fork ();

	      if (r == 0)

		{
		  if (shmflag[0] == false)
		    {
		      x = x;

		      y = y - 1;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		  // wait(NULL);

		}

	      else

		{
		  if (shmflag[0] == false)
		    {
		      wait (NULL);

		      x = x;

		      y = y + 1;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}

		      //
		    }
		}



	    }

	  else

	    {
	      if (isSafe (x, y - 1))

		{
		  if (shmflag[0] == false)
		    {
		      x = x;

		      y = y - 1;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		}

	      else

		{
		  if (shmflag[0] == false)
		    {
		      x = x;

		      y = y + 1;

		      a[count++] = matrix[x][y];
		      fprintf (fptr, "[%d:%d] ", getppid (), getpid ());
		      fprintf (fptr, "Exploring Path: ");

		      for (int i = 0; i < count; i++)

			fprintf (fptr, "%d ", a[i]);

		      fprintf (fptr, "\n");

		      if (count == len + 1 && a[len] != matrix[0][n - 1])

			{

			  fprintf (fptr, "Failed at path: ");

			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");

			}

		      if (count == len + 1 && a[len] == matrix[0][n - 1])

			{

			  fprintf (fptr, "Accepted! Followed path: ");
			  shmflag[0] = true;
			  for (int i = 0; i < count; i++)

			    fprintf (fptr, "%d ", a[i]);

			  fprintf (fptr, "\n");



			}
		    }
		}

	    }

	}

    }
  fclose (fptr);
  return 0;

}

void
Matrix (int n)
{
  int D[(n + 1) * (n + 1)][2];
  int Sum = 0;
  for (int i = 0; i < n + 1; i++)
    {
      for (int j = 0; j < n + 1; j++)
	{
	  D[i][j] = Sum;
	  Sum += 1;
	}
    }

}

struct State
{
  int id;
  int size;
  int D[1000];
  struct State *Z;
  struct State *O;
};


int
compare (struct State a, struct State b)
{
  if (a.size != b.size)
    return 0;
  for (int i = 0; i < a.size; ++i)
    {
      if (a.D[i] != b.D[i])
	return 0;
    }
  return 1;
}

int
main2 ()
{
  n--;
  int states = (n + 1) * (n + 1);

  int c[(n + 1)][(n + 1)];
  int Sum = 0;

  for (int i = 0; i < n + 1; i++)
    {
      for (int j = 0; j < n + 1; j++)
	{
	  c[i][j] = Sum;
	  Sum += 1;
	}
    }

  int NFA[2 * states + 1][states];
  for (int i = 0; i < 2 * states + 1; i++)
    {
      for (int j = 0; j < states; j++)
	{
	  NFA[i][j] = 0;
	}
    }
  // first row indicates final states
  int final_state = states - 1;
  NFA[0][final_state] = 1;


  // All Down 
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n + 1; j++)
	{
	  NFA[c[i][j] + 1][n + 1 + c[i][j]] = 1;
	}
    }

  // All Up
  for (int i = 1; i < n + 1; i++)
    {
      for (int j = 0; j < n + 1; j++)
	{
	  NFA[c[i][j] + 1][c[i][j] - n - 1] = 1;
	}
    }

  // All right 
  for (int i = 0; i < n + 1; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  NFA[c[i][j] + 1 + states][c[i][j] + 1] = 1;
	}
    }

  // All left 
  for (int i = 0; i < n + 1; i++)
    {
      for (int j = 1; j < n + 1; j++)
	{
	  NFA[c[i][j] + 1 + states][c[i][j] - 1] = 1;
	}
    }

  int z = 0;
  struct State nodes[105];
  int g = 0;
  struct State cur;
  cur.id = g;
  cur.size = 0;
  cur.D[cur.size++] = z;
  nodes[g] = cur;
  struct State wO[105];
  struct State wZ[105];

  while (z <= g)
    {
      // current state, Q[z]
      int e[1005];
      int Count = 0;
      memset (e, 0, sizeof e);
      // printf("%d \n", z);
      // printf("%d \n", g);
      for (int i = 0; i < nodes[z].size; ++i)
	{
	  int curr = nodes[z].D[i];
	  // at Z
	  for (int j = 0; j < states; ++j)
	    {
	      if (NFA[curr + 1][j] == 1 && !e[j])
		{
		  e[j] = 1;
		  Count++;
		}
	    }
	}

      struct State fromZ;
      fromZ.size = Count;
      int now = 0;
      for (int i = 0; i < states; ++i)
	{
	  if (e[i] == 1)
	    {
	      fromZ.D[now++] = i;
	    }
	}
      int have = 0;
      for (int i = 0; i <= g; ++i)
	{
	  if (compare (nodes[i], fromZ))
	    have = 1, wZ[z] = nodes[i];
	}
      if (!have)
	{
	  g++;
	  fromZ.id = g;
	  nodes[g] = fromZ;
	  wZ[z] = fromZ;
	}
      // // check this 
      nodes[z].Z = &wZ[z];

      Count = 0;
      memset (e, 0, sizeof e);
      for (int i = 0; i < nodes[z].size; ++i)
	{
	  int curr = nodes[z].D[i];
	  // at Z
	  for (int j = 0; j < states; ++j)
	    {
	      if (NFA[curr + 1 + states][j] == 1 && (!e[j]))
		{
		  e[j] = 1;
		  Count++;
		}
	    }
	}
      struct State fromO;

      fromO.size = Count;
      now = 0;
      for (int i = 0; i < states; ++i)
	{
	  if (e[i] == 1)
	    {
	      fromO.D[now++] = i;
	    }
	}
      have = 0;
      for (int i = 0; i <= g; ++i)
	{
	  if (compare (nodes[i], fromO))
	    have = 1, wO[z] = nodes[i];
	}
      if (!have)
	{
	  g++;
	  fromO.id = g;
	  nodes[g] = fromO;
	  wO[z] = fromO;
	}
      // // check this 
      nodes[z].O = &wO[z];

      z++;

    }


  int DFA[g][3];
  for (int i = 0; i <= g; ++i)
    {
      DFA[i][0] = i;
      DFA[i][1] = nodes[i].Z->id;
      DFA[i][2] = nodes[i].O->id;
    }

  int m_dfa[2 * states + 1][states];

  for (int i = 0; i < 2 * states + 1; i++)
    {
      for (int j = 0; j < states; j++)
	{
	  m_dfa[i][j] = 0;
	}
    }

  m_dfa[0][states - 1] = 1;	// Selecting the final state


  for (int i = 0; i <= g; i++)
    {
      for (int j = 1; j < 2; j++)
	{
	  m_dfa[i + 1][DFA[i][j]] = 1;
	}
    }

  for (int i = 0; i <= g; i++)
    {
      for (int j = 2; j < 3; j++)
	{
	  m_dfa[i + 1 + states][DFA[i][j]] = 1;
	}
    }

  FILE *fp = fopen ("2019B5A71106H_t2.txt", "w");
  for (int i = 0; i < 2 * states + 1; i++)
    {
      for (int j = 0; j < states; j++)
	{
	  fprintf (fp, "%d ", m_dfa[i][j]);
	}
      fprintf (fp, "\n");

    }
  fclose (fp);

}

int
main ()
{
  main1 ();
  main2 ();
}

