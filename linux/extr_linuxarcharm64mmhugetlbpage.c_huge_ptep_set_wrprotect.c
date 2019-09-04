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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int find_num_contig (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  get_clear_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_cont (int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_set_wrprotect (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void huge_ptep_set_wrprotect(struct mm_struct *mm,
			     unsigned long addr, pte_t *ptep)
{
	unsigned long pfn, dpfn;
	pgprot_t hugeprot;
	int ncontig, i;
	size_t pgsize;
	pte_t pte;

	if (!pte_cont(READ_ONCE(*ptep))) {
		ptep_set_wrprotect(mm, addr, ptep);
		return;
	}

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);
	dpfn = pgsize >> PAGE_SHIFT;

	pte = get_clear_flush(mm, addr, ptep, pgsize, ncontig);
	pte = pte_wrprotect(pte);

	hugeprot = pte_pgprot(pte);
	pfn = pte_pfn(pte);

	for (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(mm, addr, ptep, pfn_pte(pfn, hugeprot));
}