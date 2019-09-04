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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  __set_huge_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_tlb_end (unsigned long) ; 
 int /*<<< orphan*/  purge_tlb_start (unsigned long) ; 

int huge_ptep_set_access_flags(struct vm_area_struct *vma,
				unsigned long addr, pte_t *ptep,
				pte_t pte, int dirty)
{
	unsigned long flags;
	int changed;

	purge_tlb_start(flags);
	changed = !pte_same(*ptep, pte);
	if (changed) {
		__set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
	}
	purge_tlb_end(flags);
	return changed;
}