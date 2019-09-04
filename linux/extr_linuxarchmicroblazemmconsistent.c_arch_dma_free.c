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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  __free_reserved_page (struct page*) ; 
 scalar_t__ in_interrupt () ; 
 struct page* virt_to_page (void*) ; 

void arch_dma_free(struct device *dev, size_t size, void *vaddr,
		dma_addr_t dma_addr, unsigned long attrs)
{
	struct page *page;

	if (in_interrupt())
		BUG();

	size = PAGE_ALIGN(size);

#ifndef CONFIG_MMU
	/* Clear SHADOW_MASK bit in address, and free as per usual */
# ifdef CONFIG_XILINX_UNCACHED_SHADOW
	vaddr = (void *)((unsigned)vaddr & ~UNCACHED_SHADOW_MASK);
# endif
	page = virt_to_page(vaddr);

	do {
		__free_reserved_page(page);
		page++;
	} while (size -= PAGE_SIZE);
#else
	do {
		pte_t *ptep = consistent_virt_to_pte(vaddr);
		unsigned long pfn;

		if (!pte_none(*ptep) && pte_present(*ptep)) {
			pfn = pte_pfn(*ptep);
			pte_clear(&init_mm, (unsigned int)vaddr, ptep);
			if (pfn_valid(pfn)) {
				page = pfn_to_page(pfn);
				__free_reserved_page(page);
			}
		}
		vaddr += PAGE_SIZE;
	} while (size -= PAGE_SIZE);

	/* flush tlb */
	flush_tlb_all();
#endif
}