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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DMA_DIRECT_REMAP ; 
 int /*<<< orphan*/  CONFIG_DMA_REMAP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  __iommu_dma_free_pages (struct page**,int) ; 
 struct page** dma_common_find_pages (void*) ; 
 int /*<<< orphan*/  dma_common_free_remap (void*,size_t) ; 
 int /*<<< orphan*/  dma_free_contiguous (struct device*,struct page*,size_t) ; 
 scalar_t__ dma_free_from_pool (void*,size_t) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 struct page* virt_to_page (void*) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static void __iommu_dma_free(struct device *dev, size_t size, void *cpu_addr)
{
	size_t alloc_size = PAGE_ALIGN(size);
	int count = alloc_size >> PAGE_SHIFT;
	struct page *page = NULL, **pages = NULL;

	/* Non-coherent atomic allocation? Easy */
	if (IS_ENABLED(CONFIG_DMA_DIRECT_REMAP) &&
	    dma_free_from_pool(cpu_addr, alloc_size))
		return;

	if (IS_ENABLED(CONFIG_DMA_REMAP) && is_vmalloc_addr(cpu_addr)) {
		/*
		 * If it the address is remapped, then it's either non-coherent
		 * or highmem CMA, or an iommu_dma_alloc_remap() construction.
		 */
		pages = dma_common_find_pages(cpu_addr);
		if (!pages)
			page = vmalloc_to_page(cpu_addr);
		dma_common_free_remap(cpu_addr, alloc_size);
	} else {
		/* Lowmem means a coherent atomic or CMA allocation */
		page = virt_to_page(cpu_addr);
	}

	if (pages)
		__iommu_dma_free_pages(pages, count);
	if (page)
		dma_free_contiguous(dev, page, alloc_size);
}