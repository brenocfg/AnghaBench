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

/* Variables and functions */
 unsigned int mdest ; 
 unsigned int mlim ; 
 int mread (unsigned int,unsigned char*,int) ; 
 unsigned int mskip ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  scanhex (unsigned int*) ; 
 char termch ; 

__attribute__((used)) static void
memzcan(void)
{
	unsigned char v;
	unsigned a;
	int ok, ook;

	scanhex(&mdest);
	if (termch != '\n') termch = 0;
	scanhex(&mskip);
	if (termch != '\n') termch = 0;
	scanhex(&mlim);
	ook = 0;
	for (a = mdest; a < mlim; a += mskip) {
		ok = mread(a, &v, 1);
		if (ok && !ook) {
			printf("%.8x .. ", a);
		} else if (!ok && ook)
			printf("%.8lx\n", a - mskip);
		ook = ok;
		if (a + mskip < a)
			break;
	}
	if (ook)
		printf("%.8lx\n", a - mskip);
}