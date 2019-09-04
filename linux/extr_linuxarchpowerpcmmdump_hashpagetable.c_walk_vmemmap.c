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
struct pg_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void walk_vmemmap(struct pg_state *st)
{
#ifdef CONFIG_SPARSEMEM_VMEMMAP
	struct vmemmap_backing *ptr = vmemmap_list;

	/*
	 * Traverse the vmemmaped memory and dump pages that are in the hash
	 * pagetable.
	 */
	while (ptr->list) {
		hpte_find(st, ptr->virt_addr, mmu_vmemmap_psize);
		ptr = ptr->list;
	}
	seq_puts(st->seq, "---[ vmemmap end ]---\n");
#endif
}