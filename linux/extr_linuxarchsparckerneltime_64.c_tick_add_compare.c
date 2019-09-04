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
 unsigned long TICKCMP_IRQ_BIT ; 

__attribute__((used)) static int tick_add_compare(unsigned long adj)
{
	unsigned long orig_tick, new_tick, new_compare;

	__asm__ __volatile__("rd	%%tick, %0"
			     : "=r" (orig_tick));

	orig_tick &= ~TICKCMP_IRQ_BIT;

	/* Workaround for Spitfire Errata (#54 I think??), I discovered
	 * this via Sun BugID 4008234, mentioned in Solaris-2.5.1 patch
	 * number 103640.
	 *
	 * On Blackbird writes to %tick_cmpr can fail, the
	 * workaround seems to be to execute the wr instruction
	 * at the start of an I-cache line, and perform a dummy
	 * read back from %tick_cmpr right after writing to it. -DaveM
	 */
	__asm__ __volatile__("ba,pt	%%xcc, 1f\n\t"
			     " add	%1, %2, %0\n\t"
			     ".align	64\n"
			     "1:\n\t"
			     "wr	%0, 0, %%tick_cmpr\n\t"
			     "rd	%%tick_cmpr, %%g0\n\t"
			     : "=r" (new_compare)
			     : "r" (orig_tick), "r" (adj));

	__asm__ __volatile__("rd	%%tick, %0"
			     : "=r" (new_tick));
	new_tick &= ~TICKCMP_IRQ_BIT;

	return ((long)(new_tick - (orig_tick+adj))) > 0L;
}