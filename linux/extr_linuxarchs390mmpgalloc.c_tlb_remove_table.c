#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmu_table_batch {scalar_t__ nr; void** tables; } ;
struct mmu_gather {TYPE_2__* mm; struct mmu_table_batch* batch; } ;
struct TYPE_3__ {int flush_mm; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int GFP_NOWAIT ; 
 scalar_t__ MAX_TABLE_BATCH ; 
 int __GFP_NOWARN ; 
 scalar_t__ __get_free_page (int) ; 
 int /*<<< orphan*/  __tlb_flush_mm_lazy (TYPE_2__*) ; 
 int /*<<< orphan*/  tlb_flush_mmu (struct mmu_gather*) ; 
 int /*<<< orphan*/  tlb_remove_table_one (void*) ; 

void tlb_remove_table(struct mmu_gather *tlb, void *table)
{
	struct mmu_table_batch **batch = &tlb->batch;

	tlb->mm->context.flush_mm = 1;
	if (*batch == NULL) {
		*batch = (struct mmu_table_batch *)
			__get_free_page(GFP_NOWAIT | __GFP_NOWARN);
		if (*batch == NULL) {
			__tlb_flush_mm_lazy(tlb->mm);
			tlb_remove_table_one(table);
			return;
		}
		(*batch)->nr = 0;
	}
	(*batch)->tables[(*batch)->nr++] = table;
	if ((*batch)->nr == MAX_TABLE_BATCH)
		tlb_flush_mmu(tlb);
}