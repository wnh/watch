
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>



#define HERE "."

int
main(int argc, char **argv)
{

  int curdir = -1, kq, event_count;
  struct kevent change, event;
  
  if (-1 == (curdir = open(HERE, O_RDONLY | O_NONBLOCK))) {
    perror("Failure opening current directory");
    exit(1);
  }

  printf("This dir: %d\n", curdir);

  if (-1 == (kq = kqueue())) {
    perror("Failure opening kqueue");
    exit(1);
  }

  EV_SET(&change, curdir, EVFILT_VNODE, EV_ADD | EV_ENABLE, 0, 0, 0);

  for(;;)
  {
    if (-1 == (event_count = kevent(kq, &change, 1, &event, 1, NULL))) 
    {
      puts("It happend!") ;
    }
    else
    {
      puts("ERROR?");
    }
  }

  return 0;

}

