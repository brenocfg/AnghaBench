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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_flush (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t,int) ; 
 int find_num_contig (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_cont (int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pgprot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_huge_pte_at(struct mm_struct *mm, unsigned long addr,
			    pte_t *ptep, pte_t pte)
{
	size_t pgsize;
	int i;
	int ncontig;
	unsigned long pfn, dpfn;
	pgprot_t hugeprot;

	/*
	 * Code needs to be expanded to handle huge swap and migration
	 * entries. Needed for HUGETLB and MEMORY_FAILURE.
	 */
	WARN_ON(!pte_present(pte));

	if (!pte_cont(pte)) {
		set_pte_at(mm, addr, ptep, pte);
		return;
	}

	ncontig = find_num_contig(mm, addr, ptep, &pgsize);
	pfn = pte_pfn(pte);
	dpfn = pgsize >> PAGE_SHIFT;
	hugeprot = pte_pgprot(pte);

	clear_flush(mm, addr, ptep, pgsize, ncontig);

	for (i = 0; i < ncontig; i++, ptep++, addr += pgsize, pfn += dpfn)
		set_pte_at(mm, addr, ptep, pfn_pte(pfn, hugeprot));
}