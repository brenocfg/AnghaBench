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
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ PageReserved (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page_all (struct mm_struct*,struct page*) ; 
 scalar_t__ hypervisor ; 
 scalar_t__ page_address (struct page*) ; 
 struct address_space* page_mapping_file (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_exec (int /*<<< orphan*/ ) ; 
 unsigned long pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlb_batch_add_one (struct mm_struct*,unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ tlb_type ; 

void tlb_batch_add(struct mm_struct *mm, unsigned long vaddr,
		   pte_t *ptep, pte_t orig, int fullmm,
		   unsigned int hugepage_shift)
{
	if (tlb_type != hypervisor &&
	    pte_dirty(orig)) {
		unsigned long paddr, pfn = pte_pfn(orig);
		struct address_space *mapping;
		struct page *page;

		if (!pfn_valid(pfn))
			goto no_cache_flush;

		page = pfn_to_page(pfn);
		if (PageReserved(page))
			goto no_cache_flush;

		/* A real file page? */
		mapping = page_mapping_file(page);
		if (!mapping)
			goto no_cache_flush;

		paddr = (unsigned long) page_address(page);
		if ((paddr ^ vaddr) & (1 << 13))
			flush_dcache_page_all(mm, page);
	}

no_cache_flush:
	if (!fullmm)
		tlb_batch_add_one(mm, vaddr, pte_exec(orig), hugepage_shift);
}