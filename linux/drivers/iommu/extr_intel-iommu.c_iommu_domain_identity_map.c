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
struct dmar_domain {int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int DMA_PTE_READ ; 
 int DMA_PTE_WRITE ; 
 int ENOMEM ; 
 unsigned long long VTD_PAGE_SHIFT ; 
 int __domain_mapping (struct dmar_domain*,unsigned long,int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  dma_pte_clear_range (struct dmar_domain*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dma_to_mm_pfn (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reserve_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iommu_domain_identity_map(struct dmar_domain *domain,
				     unsigned long long start,
				     unsigned long long end)
{
	unsigned long first_vpfn = start >> VTD_PAGE_SHIFT;
	unsigned long last_vpfn = end >> VTD_PAGE_SHIFT;

	if (!reserve_iova(&domain->iovad, dma_to_mm_pfn(first_vpfn),
			  dma_to_mm_pfn(last_vpfn))) {
		pr_err("Reserving iova failed\n");
		return -ENOMEM;
	}

	pr_debug("Mapping reserved region %llx-%llx\n", start, end);
	/*
	 * RMRR range might have overlap with physical memory range,
	 * clear it first
	 */
	dma_pte_clear_range(domain, first_vpfn, last_vpfn);

	return __domain_mapping(domain, first_vpfn, NULL,
				first_vpfn, last_vpfn - first_vpfn + 1,
				DMA_PTE_READ|DMA_PTE_WRITE);
}