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
typedef  int /*<<< orphan*/  u32 ;
struct subpage_prot_table {unsigned long maxaddr; int /*<<< orphan*/ *** protptrs; int /*<<< orphan*/ ** low_prot; } ;
struct TYPE_2__ {struct subpage_prot_table spt; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 unsigned long SBP_L2_COUNT ; 
 int TASK_SIZE_USER64 ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

void subpage_prot_free(struct mm_struct *mm)
{
	struct subpage_prot_table *spt = &mm->context.spt;
	unsigned long i, j, addr;
	u32 **p;

	for (i = 0; i < 4; ++i) {
		if (spt->low_prot[i]) {
			free_page((unsigned long)spt->low_prot[i]);
			spt->low_prot[i] = NULL;
		}
	}
	addr = 0;
	for (i = 0; i < (TASK_SIZE_USER64 >> 43); ++i) {
		p = spt->protptrs[i];
		if (!p)
			continue;
		spt->protptrs[i] = NULL;
		for (j = 0; j < SBP_L2_COUNT && addr < spt->maxaddr;
		     ++j, addr += PAGE_SIZE)
			if (p[j])
				free_page((unsigned long)p[j]);
		free_page((unsigned long)p);
	}
	spt->maxaddr = 0;
}