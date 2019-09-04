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
struct dma_ops_domain {int /*<<< orphan*/  iovad; int /*<<< orphan*/  domain; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int __roundup_pow_of_two (unsigned int) ; 
 scalar_t__ amd_iommu_unmap_flush ; 
 int /*<<< orphan*/  dma_ops_free_iova (struct dma_ops_domain*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  domain_flush_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_flush_tlb (int /*<<< orphan*/ *) ; 
 unsigned int iommu_num_pages (unsigned int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  iommu_unmap_page (int /*<<< orphan*/ *,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  queue_iova (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __unmap_single(struct dma_ops_domain *dma_dom,
			   dma_addr_t dma_addr,
			   size_t size,
			   int dir)
{
	dma_addr_t i, start;
	unsigned int pages;

	pages = iommu_num_pages(dma_addr, size, PAGE_SIZE);
	dma_addr &= PAGE_MASK;
	start = dma_addr;

	for (i = 0; i < pages; ++i) {
		iommu_unmap_page(&dma_dom->domain, start, PAGE_SIZE);
		start += PAGE_SIZE;
	}

	if (amd_iommu_unmap_flush) {
		domain_flush_tlb(&dma_dom->domain);
		domain_flush_complete(&dma_dom->domain);
		dma_ops_free_iova(dma_dom, dma_addr, pages);
	} else {
		pages = __roundup_pow_of_two(pages);
		queue_iova(&dma_dom->iovad, dma_addr >> PAGE_SHIFT, pages, 0);
	}
}