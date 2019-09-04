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
 int PTRS_PER_PGD ; 
 scalar_t__ invalid_pud_table ; 

void pgd_init(unsigned long page)
{
	unsigned long *p, *end;
	unsigned long entry;

#if !defined(__PAGETABLE_PUD_FOLDED)
	entry = (unsigned long)invalid_pud_table;
#elif !defined(__PAGETABLE_PMD_FOLDED)
	entry = (unsigned long)invalid_pmd_table;
#else
	entry = (unsigned long)invalid_pte_table;
#endif

	p = (unsigned long *) page;
	end = p + PTRS_PER_PGD;

	do {
		p[0] = entry;
		p[1] = entry;
		p[2] = entry;
		p[3] = entry;
		p[4] = entry;
		p += 8;
		p[-3] = entry;
		p[-2] = entry;
		p[-1] = entry;
	} while (p != end);
}