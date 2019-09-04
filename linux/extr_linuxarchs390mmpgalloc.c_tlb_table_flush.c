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
struct mmu_table_batch {int /*<<< orphan*/  rcu; } ;
struct mmu_gather {struct mmu_table_batch* batch; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_sched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_remove_table_rcu ; 

void tlb_table_flush(struct mmu_gather *tlb)
{
	struct mmu_table_batch **batch = &tlb->batch;

	if (*batch) {
		call_rcu_sched(&(*batch)->rcu, tlb_remove_table_rcu);
		*batch = NULL;
	}
}