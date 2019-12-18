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
struct dmar_domain {int /*<<< orphan*/ * pgd; int /*<<< orphan*/  gaw; int /*<<< orphan*/  agaw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DOMAIN_MAX_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agaw_to_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pte_clear_range (struct dmar_domain*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dma_pte_free_level (struct dmar_domain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  domain_pfn_supported (struct dmar_domain*,unsigned long) ; 
 int /*<<< orphan*/  free_pgtable_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_pte_free_pagetable(struct dmar_domain *domain,
				   unsigned long start_pfn,
				   unsigned long last_pfn,
				   int retain_level)
{
	BUG_ON(!domain_pfn_supported(domain, start_pfn));
	BUG_ON(!domain_pfn_supported(domain, last_pfn));
	BUG_ON(start_pfn > last_pfn);

	dma_pte_clear_range(domain, start_pfn, last_pfn);

	/* We don't need lock here; nobody else touches the iova range */
	dma_pte_free_level(domain, agaw_to_level(domain->agaw), retain_level,
			   domain->pgd, 0, start_pfn, last_pfn);

	/* free pgd */
	if (start_pfn == 0 && last_pfn == DOMAIN_MAX_PFN(domain->gaw)) {
		free_pgtable_page(domain->pgd);
		domain->pgd = NULL;
	}
}