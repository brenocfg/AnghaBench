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
typedef  void page ;
struct device {int coherent_dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DMA_ATTR_NO_KERNEL_MAPPING ; 
 int GFP_DMA ; 
 unsigned long PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_SHIFT ; 
 int __GFP_DMA ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __invalidate_dcache_range (unsigned long,size_t) ; 
 void* alloc_pages (int,int /*<<< orphan*/ ) ; 
 void* dma_alloc_from_contiguous (struct device*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 scalar_t__ gfpflags_allow_blocking (int) ; 
 scalar_t__ page_address (void*) ; 
 int /*<<< orphan*/  page_to_phys (void*) ; 
 int /*<<< orphan*/  phys_to_dma (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_vaddr_cached (scalar_t__) ; 
 void* platform_vaddr_to_uncached (scalar_t__) ; 

void *arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *handle,
		gfp_t flag, unsigned long attrs)
{
	unsigned long count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	struct page *page = NULL;

	/* ignore region speicifiers */

	flag &= ~(__GFP_DMA | __GFP_HIGHMEM);

	if (dev == NULL || (dev->coherent_dma_mask < 0xffffffff))
		flag |= GFP_DMA;

	if (gfpflags_allow_blocking(flag))
		page = dma_alloc_from_contiguous(dev, count, get_order(size),
						 flag & __GFP_NOWARN);

	if (!page)
		page = alloc_pages(flag, get_order(size));

	if (!page)
		return NULL;

	*handle = phys_to_dma(dev, page_to_phys(page));

	if (attrs & DMA_ATTR_NO_KERNEL_MAPPING) {
		return page;
	}

#ifdef CONFIG_MMU
	if (PageHighMem(page)) {
		void *p;

		p = dma_common_contiguous_remap(page, size, VM_MAP,
						pgprot_noncached(PAGE_KERNEL),
						__builtin_return_address(0));
		if (!p) {
			if (!dma_release_from_contiguous(dev, page, count))
				__free_pages(page, get_order(size));
		}
		return p;
	}
#endif
	BUG_ON(!platform_vaddr_cached(page_address(page)));
	__invalidate_dcache_range((unsigned long)page_address(page), size);
	return platform_vaddr_to_uncached(page_address(page));
}