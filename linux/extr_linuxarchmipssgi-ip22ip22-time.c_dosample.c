#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int tcword; int tcnt2; } ;

/* Variables and functions */
 int HZ ; 
 int SGINT_TCSAMP_COUNTER ; 
 int SGINT_TCWORD_CALL ; 
 int SGINT_TCWORD_CLAT ; 
 int SGINT_TCWORD_CNT2 ; 
 int SGINT_TCWORD_MRGEN ; 
 int SGINT_TCWORD_MSWST ; 
 int read_c0_count () ; 
 scalar_t__ readb (int*) ; 
 TYPE_1__* sgint ; 
 int /*<<< orphan*/  writeb (int,int*) ; 

__attribute__((used)) static unsigned long dosample(void)
{
	u32 ct0, ct1;
	u8 msb;

	/* Start the counter. */
	sgint->tcword = (SGINT_TCWORD_CNT2 | SGINT_TCWORD_CALL |
			 SGINT_TCWORD_MRGEN);
	sgint->tcnt2 = SGINT_TCSAMP_COUNTER & 0xff;
	sgint->tcnt2 = SGINT_TCSAMP_COUNTER >> 8;

	/* Get initial counter invariant */
	ct0 = read_c0_count();

	/* Latch and spin until top byte of counter2 is zero */
	do {
		writeb(SGINT_TCWORD_CNT2 | SGINT_TCWORD_CLAT, &sgint->tcword);
		(void) readb(&sgint->tcnt2);
		msb = readb(&sgint->tcnt2);
		ct1 = read_c0_count();
	} while (msb);

	/* Stop the counter. */
	writeb(SGINT_TCWORD_CNT2 | SGINT_TCWORD_CALL | SGINT_TCWORD_MSWST,
	       &sgint->tcword);
	/*
	 * Return the difference, this is how far the r4k counter increments
	 * for every 1/HZ seconds. We round off the nearest 1 MHz of master
	 * clock (= 1000000 / HZ / 2).
	 */

	return (ct1 - ct0) / (500000/HZ) * (500000/HZ);
}