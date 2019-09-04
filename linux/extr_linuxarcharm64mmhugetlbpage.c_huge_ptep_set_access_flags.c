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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __cont_access_flags_changed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int find_num_contig (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  get_clear_flush (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_cont (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pgprot (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_young (int /*<<< orphan*/ ) ; 
 int ptep_set_access_flags (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int huge_ptep_set_access_flags(struct vm_area_struct *vma,
			       unsigned long addr, pte_t *ptep,
			       pte_t pte, int dirty)
{
	int ncontig, i;
	size_t pgsize = 0;
	unsigned long pfn = pte_pfn(pte), dpfn;
	pgprot_t hugeprot;
	pte_t orig_pte;

	if (!pte_cont(pte))
		return ptep_set_access_flags(vma, addr, ptep, pte, dirty);

	ncontig = find_num_contig(vma->vm_mm, addr, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	if (!__cont_access_flags_changed(ptep, pte, ncontig))
		return 0;

	orig_pte = get_clear_flush(vma->vm_mm, addr, ptep, pgsize, ncontig);

	/* Make sure we don't lose the dirty or young state */
	if (pte_dirty(orig_pte))
		pte = pte_mkdirty(pte);

	if (pte_young(orig_pte))
		pte = pte_mkyoung(pte);

	hugeprot = pte_pgprot(pte);
	for (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(vma->vm_mm, addr, ptep, pfn_pte(pfn, hugeprot));

	return 1;
}