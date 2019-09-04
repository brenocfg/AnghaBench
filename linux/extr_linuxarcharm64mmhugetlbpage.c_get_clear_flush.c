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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 struct vm_area_struct TLB_FLUSH_VMA (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  huge_ptep_get (int /*<<< orphan*/ *) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int pte_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pte_t get_clear_flush(struct mm_struct *mm,
			     unsigned long addr,
			     pte_t *ptep,
			     unsigned long pgsize,
			     unsigned long ncontig)
{
	pte_t orig_pte = huge_ptep_get(ptep);
	bool valid = pte_valid(orig_pte);
	unsigned long i, saddr = addr;

	for (i = 0; i < ncontig; i++, addr += pgsize, ptep++) {
		pte_t pte = ptep_get_and_clear(mm, addr, ptep);

		/*
		 * If HW_AFDBM is enabled, then the HW could turn on
		 * the dirty or accessed bit for any page in the set,
		 * so check them all.
		 */
		if (pte_dirty(pte))
			orig_pte = pte_mkdirty(orig_pte);

		if (pte_young(pte))
			orig_pte = pte_mkyoung(orig_pte);
	}

	if (valid) {
		struct vm_area_struct vma = TLB_FLUSH_VMA(mm, 0);
		flush_tlb_range(&vma, saddr, addr);
	}
	return orig_pte;
}