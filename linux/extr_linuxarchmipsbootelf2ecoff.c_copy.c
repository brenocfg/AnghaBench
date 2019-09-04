#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void copy(int out, int in, off_t offset, off_t size)
{
	char ibuf[4096];
	int remaining, cur, count;

	/* Go to the start of the ELF symbol table... */
	if (lseek(in, offset, SEEK_SET) < 0) {
		perror("copy: lseek");
		exit(1);
	}

	remaining = size;
	while (remaining) {
		cur = remaining;
		if (cur > sizeof ibuf)
			cur = sizeof ibuf;
		remaining -= cur;
		if ((count = read(in, ibuf, cur)) != cur) {
			fprintf(stderr, "copy: read: %s\n",
				count ? strerror(errno) :
				"premature end of file");
			exit(1);
		}
		if ((count = write(out, ibuf, cur)) != cur) {
			perror("copy: write");
			exit(1);
		}
	}
}