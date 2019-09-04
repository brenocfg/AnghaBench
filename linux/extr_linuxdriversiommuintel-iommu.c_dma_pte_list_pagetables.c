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
struct page {struct page* freelist; } ;
struct dmar_domain {int dummy; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int dma_pte_addr (struct dma_pte*) ; 
 scalar_t__ dma_pte_present (struct dma_pte*) ; 
 int /*<<< orphan*/  dma_pte_superpage (struct dma_pte*) ; 
 int /*<<< orphan*/  first_pte_in_page (struct dma_pte*) ; 
 struct dma_pte* page_address (struct page*) ; 
 struct page* pfn_to_page (int) ; 

__attribute__((used)) static struct page *dma_pte_list_pagetables(struct dmar_domain *domain,
					    int level, struct dma_pte *pte,
					    struct page *freelist)
{
	struct page *pg;

	pg = pfn_to_page(dma_pte_addr(pte) >> PAGE_SHIFT);
	pg->freelist = freelist;
	freelist = pg;

	if (level == 1)
		return freelist;

	pte = page_address(pg);
	do {
		if (dma_pte_present(pte) && !dma_pte_superpage(pte))
			freelist = dma_pte_list_pagetables(domain, level - 1,
							   pte, freelist);
		pte++;
	} while (!first_pte_in_page(pte));

	return freelist;
}