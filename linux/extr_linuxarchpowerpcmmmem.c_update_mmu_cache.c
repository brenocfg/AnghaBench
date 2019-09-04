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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */

void update_mmu_cache(struct vm_area_struct *vma, unsigned long address,
		      pte_t *ptep)
{
#ifdef CONFIG_PPC_STD_MMU
	/*
	 * We don't need to worry about _PAGE_PRESENT here because we are
	 * called with either mm->page_table_lock held or ptl lock held
	 */
	unsigned long access, trap;

	if (radix_enabled()) {
		prefetch((void *)address);
		return;
	}

	/* We only want HPTEs for linux PTEs that have _PAGE_ACCESSED set */
	if (!pte_young(*ptep) || address >= TASK_SIZE)
		return;

	/* We try to figure out if we are coming from an instruction
	 * access fault and pass that down to __hash_page so we avoid
	 * double-faulting on execution of fresh text. We have to test
	 * for regs NULL since init will get here first thing at boot
	 *
	 * We also avoid filling the hash if not coming from a fault
	 */

	trap = current->thread.regs ? TRAP(current->thread.regs) : 0UL;
	switch (trap) {
	case 0x300:
		access = 0UL;
		break;
	case 0x400:
		access = _PAGE_EXEC;
		break;
	default:
		return;
	}

	hash_preload(vma->vm_mm, address, access, trap);
#endif /* CONFIG_PPC_STD_MMU */
#if (defined(CONFIG_PPC_BOOK3E_64) || defined(CONFIG_PPC_FSL_BOOK3E)) \
	&& defined(CONFIG_HUGETLB_PAGE)
	if (is_vm_hugetlb_page(vma))
		book3e_hugetlb_preload(vma, address, *ptep);
#endif
}