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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DMA_DIRECT_REMAP ; 
 int /*<<< orphan*/  CONFIG_DMA_REMAP ; 
 unsigned long DMA_ATTR_FORCE_CONTIGUOUS ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  __GFP_ZERO ; 
 int /*<<< orphan*/  __iommu_dma_free (struct device*,size_t,void*) ; 
 int /*<<< orphan*/  __iommu_dma_map (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 int dev_is_dma_coherent (struct device*) ; 
 void* dma_alloc_from_pool (int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ ) ; 
 int dma_info_to_prot (int /*<<< orphan*/ ,int,unsigned long) ; 
 scalar_t__ gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 void* iommu_dma_alloc_pages (struct device*,size_t,struct page**,int /*<<< orphan*/ ,unsigned long) ; 
 void* iommu_dma_alloc_remap (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 

__attribute__((used)) static void *iommu_dma_alloc(struct device *dev, size_t size,
		dma_addr_t *handle, gfp_t gfp, unsigned long attrs)
{
	bool coherent = dev_is_dma_coherent(dev);
	int ioprot = dma_info_to_prot(DMA_BIDIRECTIONAL, coherent, attrs);
	struct page *page = NULL;
	void *cpu_addr;

	gfp |= __GFP_ZERO;

	if (IS_ENABLED(CONFIG_DMA_REMAP) && gfpflags_allow_blocking(gfp) &&
	    !(attrs & DMA_ATTR_FORCE_CONTIGUOUS))
		return iommu_dma_alloc_remap(dev, size, handle, gfp, attrs);

	if (IS_ENABLED(CONFIG_DMA_DIRECT_REMAP) &&
	    !gfpflags_allow_blocking(gfp) && !coherent)
		cpu_addr = dma_alloc_from_pool(PAGE_ALIGN(size), &page, gfp);
	else
		cpu_addr = iommu_dma_alloc_pages(dev, size, &page, gfp, attrs);
	if (!cpu_addr)
		return NULL;

	*handle = __iommu_dma_map(dev, page_to_phys(page), size, ioprot);
	if (*handle == DMA_MAPPING_ERROR) {
		__iommu_dma_free(dev, size, cpu_addr);
		return NULL;
	}

	return cpu_addr;
}