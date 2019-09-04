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
struct mm_struct {unsigned long brk; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ brk_rnd () ; 

unsigned long arch_randomize_brk(struct mm_struct *mm)
{
	unsigned long base = mm->brk;
	unsigned long ret;

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * If we are using 1TB segments and we are allowed to randomise
	 * the heap, we can put it above 1TB so it is backed by a 1TB
	 * segment. Otherwise the heap will be in the bottom 1TB
	 * which always uses 256MB segments and this may result in a
	 * performance penalty. We don't need to worry about radix. For
	 * radix, mmu_highuser_ssize remains unchanged from 256MB.
	 */
	if (!is_32bit_task() && (mmu_highuser_ssize == MMU_SEGSIZE_1T))
		base = max_t(unsigned long, mm->brk, 1UL << SID_SHIFT_1T);
#endif

	ret = PAGE_ALIGN(base + brk_rnd());

	if (ret < mm->brk)
		return mm->brk;

	return ret;
}