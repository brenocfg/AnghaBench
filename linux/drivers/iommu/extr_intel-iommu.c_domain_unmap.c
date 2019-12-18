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
struct dmar_domain {int /*<<< orphan*/ * pgd; int /*<<< orphan*/  gaw; int /*<<< orphan*/  agaw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DOMAIN_MAX_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agaw_to_level (int /*<<< orphan*/ ) ; 
 struct page* dma_pte_clear_level (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_pfn_supported (struct dmar_domain*,unsigned long) ; 
 struct page* virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *domain_unmap(struct dmar_domain *domain,
				 unsigned long start_pfn,
				 unsigned long last_pfn)
{
	struct page *freelist;

	BUG_ON(!domain_pfn_supported(domain, start_pfn));
	BUG_ON(!domain_pfn_supported(domain, last_pfn));
	BUG_ON(start_pfn > last_pfn);

	/* we don't need lock here; nobody else touches the iova range */
	freelist = dma_pte_clear_level(domain, agaw_to_level(domain->agaw),
				       domain->pgd, 0, start_pfn, last_pfn, NULL);

	/* free pgd */
	if (start_pfn == 0 && last_pfn == DOMAIN_MAX_PFN(domain->gaw)) {
		struct page *pgd_page = virt_to_page(domain->pgd);
		pgd_page->freelist = freelist;
		freelist = pgd_page;

		domain->pgd = NULL;
	}

	return freelist;
}