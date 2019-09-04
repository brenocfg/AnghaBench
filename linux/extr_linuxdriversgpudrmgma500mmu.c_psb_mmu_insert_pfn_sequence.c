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
typedef  unsigned long uint32_t ;
struct psb_mmu_pt {int /*<<< orphan*/  count; } ;
struct psb_mmu_pd {int hw_context; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psb_mmu_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  psb_mmu_flush_ptes (struct psb_mmu_pd*,unsigned long,unsigned long,int,int) ; 
 unsigned long psb_mmu_mask_pte (int /*<<< orphan*/ ,int) ; 
 struct psb_mmu_pt* psb_mmu_pt_alloc_map_lock (struct psb_mmu_pd*,unsigned long) ; 
 int /*<<< orphan*/  psb_mmu_pt_unmap_unlock (struct psb_mmu_pt*) ; 
 int /*<<< orphan*/  psb_mmu_set_pte (struct psb_mmu_pt*,unsigned long,unsigned long) ; 
 unsigned long psb_pd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int psb_mmu_insert_pfn_sequence(struct psb_mmu_pd *pd, uint32_t start_pfn,
				unsigned long address, uint32_t num_pages,
				int type)
{
	struct psb_mmu_pt *pt;
	uint32_t pte;
	unsigned long addr;
	unsigned long end;
	unsigned long next;
	unsigned long f_address = address;
	int ret = -ENOMEM;

	down_read(&pd->driver->sem);

	addr = address;
	end = addr + (num_pages << PAGE_SHIFT);

	do {
		next = psb_pd_addr_end(addr, end);
		pt = psb_mmu_pt_alloc_map_lock(pd, addr);
		if (!pt) {
			ret = -ENOMEM;
			goto out;
		}
		do {
			pte = psb_mmu_mask_pte(start_pfn++, type);
			psb_mmu_set_pte(pt, addr, pte);
			pt->count++;
		} while (addr += PAGE_SIZE, addr < next);
		psb_mmu_pt_unmap_unlock(pt);

	} while (addr = next, next != end);
	ret = 0;

out:
	if (pd->hw_context != -1)
		psb_mmu_flush_ptes(pd, f_address, num_pages, 1, 1);

	up_read(&pd->driver->sem);

	if (pd->hw_context != -1)
		psb_mmu_flush(pd->driver);

	return 0;
}