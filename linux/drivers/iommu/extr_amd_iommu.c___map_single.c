#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct dma_ops_domain {TYPE_1__ domain; } ;
struct device {int dummy; } ;
typedef  int phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int dir2prot (int) ; 
 int dma_ops_alloc_iova (struct device*,struct dma_ops_domain*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ops_free_iova (struct dma_ops_domain*,int,unsigned int) ; 
 int /*<<< orphan*/  domain_flush_complete (TYPE_1__*) ; 
 int /*<<< orphan*/  domain_flush_np_cache (TYPE_1__*,int,size_t) ; 
 int /*<<< orphan*/  domain_flush_tlb (TYPE_1__*) ; 
 int iommu_map_page (TYPE_1__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 unsigned int iommu_num_pages (int,size_t,int) ; 
 int /*<<< orphan*/  iommu_unmap_page (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static dma_addr_t __map_single(struct device *dev,
			       struct dma_ops_domain *dma_dom,
			       phys_addr_t paddr,
			       size_t size,
			       enum dma_data_direction direction,
			       u64 dma_mask)
{
	dma_addr_t offset = paddr & ~PAGE_MASK;
	dma_addr_t address, start, ret;
	unsigned long flags;
	unsigned int pages;
	int prot = 0;
	int i;

	pages = iommu_num_pages(paddr, size, PAGE_SIZE);
	paddr &= PAGE_MASK;

	address = dma_ops_alloc_iova(dev, dma_dom, pages, dma_mask);
	if (!address)
		goto out;

	prot = dir2prot(direction);

	start = address;
	for (i = 0; i < pages; ++i) {
		ret = iommu_map_page(&dma_dom->domain, start, paddr,
				     PAGE_SIZE, prot, GFP_ATOMIC);
		if (ret)
			goto out_unmap;

		paddr += PAGE_SIZE;
		start += PAGE_SIZE;
	}
	address += offset;

	domain_flush_np_cache(&dma_dom->domain, address, size);

out:
	return address;

out_unmap:

	for (--i; i >= 0; --i) {
		start -= PAGE_SIZE;
		iommu_unmap_page(&dma_dom->domain, start, PAGE_SIZE);
	}

	spin_lock_irqsave(&dma_dom->domain.lock, flags);
	domain_flush_tlb(&dma_dom->domain);
	domain_flush_complete(&dma_dom->domain);
	spin_unlock_irqrestore(&dma_dom->domain.lock, flags);

	dma_ops_free_iova(dma_dom, address, pages);

	return DMA_MAPPING_ERROR;
}