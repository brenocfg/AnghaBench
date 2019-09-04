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
typedef  scalar_t__ u32 ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DMA_ATTR_NON_CONSISTENT ; 
 int __GFP_HIGHMEM ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned long) ; 
 struct page* alloc_pages (int,unsigned long) ; 
 int /*<<< orphan*/  dma_cache_wback_inv (scalar_t__,size_t) ; 
 unsigned long get_order (size_t) ; 
 void* ioremap_nocache (scalar_t__,size_t) ; 
 scalar_t__ page_to_phys (struct page*) ; 

void *arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	unsigned long order = get_order(size);
	struct page *page;
	phys_addr_t paddr;
	void *kvaddr;
	bool need_coh = !(attrs & DMA_ATTR_NON_CONSISTENT);

	/*
	 * __GFP_HIGHMEM flag is cleared by upper layer functions
	 * (in include/linux/dma-mapping.h) so we should never get a
	 * __GFP_HIGHMEM here.
	 */
	BUG_ON(gfp & __GFP_HIGHMEM);

	page = alloc_pages(gfp, order);
	if (!page)
		return NULL;

	/* This is linear addr (0x8000_0000 based) */
	paddr = page_to_phys(page);

	*dma_handle = paddr;

	/*
	 * A coherent buffer needs MMU mapping to enforce non-cachability.
	 * kvaddr is kernel Virtual address (0x7000_0000 based).
	 */
	if (need_coh) {
		kvaddr = ioremap_nocache(paddr, size);
		if (kvaddr == NULL) {
			__free_pages(page, order);
			return NULL;
		}
	} else {
		kvaddr = (void *)(u32)paddr;
	}

	/*
	 * Evict any existing L1 and/or L2 lines for the backing page
	 * in case it was used earlier as a normal "cached" page.
	 * Yeah this bit us - STAR 9000898266
	 *
	 * Although core does call flush_cache_vmap(), it gets kvaddr hence
	 * can't be used to efficiently flush L1 and/or L2 which need paddr
	 * Currently flush_cache_vmap nukes the L1 cache completely which
	 * will be optimized as a separate commit
	 */
	if (need_coh)
		dma_cache_wback_inv(paddr, size);

	return kvaddr;
}