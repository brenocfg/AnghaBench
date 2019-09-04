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
typedef  int /*<<< orphan*/  u64 ;
struct dma_ops_domain {int /*<<< orphan*/  domain; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ AMD_IOMMU_MAPPING_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  amd_iommu_np_cache ; 
 int dir2prot (int) ; 
 scalar_t__ dma_ops_alloc_iova (struct device*,struct dma_ops_domain*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_ops_free_iova (struct dma_ops_domain*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  domain_flush_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_flush_pages (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  domain_flush_tlb (int /*<<< orphan*/ *) ; 
 scalar_t__ iommu_map_page (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 unsigned int iommu_num_pages (scalar_t__,size_t,scalar_t__) ; 
 int /*<<< orphan*/  iommu_unmap_page (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_addr_t __map_single(struct device *dev,
			       struct dma_ops_domain *dma_dom,
			       phys_addr_t paddr,
			       size_t size,
			       enum dma_data_direction direction,
			       u64 dma_mask)
{
	dma_addr_t offset = paddr & ~PAGE_MASK;
	dma_addr_t address, start, ret;
	unsigned int pages;
	int prot = 0;
	int i;

	pages = iommu_num_pages(paddr, size, PAGE_SIZE);
	paddr &= PAGE_MASK;

	address = dma_ops_alloc_iova(dev, dma_dom, pages, dma_mask);
	if (address == AMD_IOMMU_MAPPING_ERROR)
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

	if (unlikely(amd_iommu_np_cache)) {
		domain_flush_pages(&dma_dom->domain, address, size);
		domain_flush_complete(&dma_dom->domain);
	}

out:
	return address;

out_unmap:

	for (--i; i >= 0; --i) {
		start -= PAGE_SIZE;
		iommu_unmap_page(&dma_dom->domain, start, PAGE_SIZE);
	}

	domain_flush_tlb(&dma_dom->domain);
	domain_flush_complete(&dma_dom->domain);

	dma_ops_free_iova(dma_dom, address, pages);

	return AMD_IOMMU_MAPPING_ERROR;
}