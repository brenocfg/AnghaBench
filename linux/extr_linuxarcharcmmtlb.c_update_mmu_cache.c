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
struct vm_area_struct {int vm_flags; } ;
struct page {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PG_dc_clean ; 
 int VM_EXEC ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __inv_icache_page (unsigned long,unsigned long) ; 
 scalar_t__ addr_not_cache_congruent (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  create_tlb (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void update_mmu_cache(struct vm_area_struct *vma, unsigned long vaddr_unaligned,
		      pte_t *ptep)
{
	unsigned long vaddr = vaddr_unaligned & PAGE_MASK;
	phys_addr_t paddr = pte_val(*ptep) & PAGE_MASK;
	struct page *page = pfn_to_page(pte_pfn(*ptep));

	create_tlb(vma, vaddr, ptep);

	if (page == ZERO_PAGE(0)) {
		return;
	}

	/*
	 * Exec page : Independent of aliasing/page-color considerations,
	 *	       since icache doesn't snoop dcache on ARC, any dirty
	 *	       K-mapping of a code page needs to be wback+inv so that
	 *	       icache fetch by userspace sees code correctly.
	 * !EXEC page: If K-mapping is NOT congruent to U-mapping, flush it
	 *	       so userspace sees the right data.
	 *  (Avoids the flush for Non-exec + congruent mapping case)
	 */
	if ((vma->vm_flags & VM_EXEC) ||
	     addr_not_cache_congruent(paddr, vaddr)) {

		int dirty = !test_and_set_bit(PG_dc_clean, &page->flags);
		if (dirty) {
			/* wback + inv dcache lines (K-mapping) */
			__flush_dcache_page(paddr, paddr);

			/* invalidate any existing icache lines (U-mapping) */
			if (vma->vm_flags & VM_EXEC)
				__inv_icache_page(paddr, vaddr);
		}
	}
}