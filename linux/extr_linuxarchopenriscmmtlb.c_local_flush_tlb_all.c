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
 unsigned long NUM_ITLB_SETS ; 
 int /*<<< orphan*/  SPR_DTLBMR_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPR_ITLBMR_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr_off (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void local_flush_tlb_all(void)
{
	int i;
	unsigned long num_tlb_sets;

	/* Determine number of sets for IMMU. */
	/* FIXME: Assumption is I & D nsets equal. */
	num_tlb_sets = NUM_ITLB_SETS;

	for (i = 0; i < num_tlb_sets; i++) {
		mtspr_off(SPR_DTLBMR_BASE(0), i, 0);
		mtspr_off(SPR_ITLBMR_BASE(0), i, 0);
	}
}