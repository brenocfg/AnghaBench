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
typedef  scalar_t__ u64 ;
struct protection_domain {int dummy; } ;
struct page {int dummy; } ;
struct dma_ops_domain {int dummy; } ;
struct device {scalar_t__* dma_mask; scalar_t__ coherent_dma_mask; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IS_ERR (struct protection_domain*) ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PTR_ERR (struct protection_domain*) ; 
 int __GFP_DMA ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __map_single (struct device*,struct dma_ops_domain*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 struct page* alloc_pages (int,int /*<<< orphan*/ ) ; 
 struct page* dma_alloc_from_contiguous (struct device*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_release_from_contiguous (struct device*,struct page*,size_t) ; 
 struct protection_domain* get_domain (struct device*) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 struct dma_ops_domain* to_dma_ops_domain (struct protection_domain*) ; 

__attribute__((used)) static void *alloc_coherent(struct device *dev, size_t size,
			    dma_addr_t *dma_addr, gfp_t flag,
			    unsigned long attrs)
{
	u64 dma_mask = dev->coherent_dma_mask;
	struct protection_domain *domain;
	struct dma_ops_domain *dma_dom;
	struct page *page;

	domain = get_domain(dev);
	if (PTR_ERR(domain) == -EINVAL) {
		page = alloc_pages(flag, get_order(size));
		*dma_addr = page_to_phys(page);
		return page_address(page);
	} else if (IS_ERR(domain))
		return NULL;

	dma_dom   = to_dma_ops_domain(domain);
	size	  = PAGE_ALIGN(size);
	dma_mask  = dev->coherent_dma_mask;
	flag     &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);
	flag     |= __GFP_ZERO;

	page = alloc_pages(flag | __GFP_NOWARN,  get_order(size));
	if (!page) {
		if (!gfpflags_allow_blocking(flag))
			return NULL;

		page = dma_alloc_from_contiguous(dev, size >> PAGE_SHIFT,
					get_order(size), flag & __GFP_NOWARN);
		if (!page)
			return NULL;
	}

	if (!dma_mask)
		dma_mask = *dev->dma_mask;

	*dma_addr = __map_single(dev, dma_dom, page_to_phys(page),
				 size, DMA_BIDIRECTIONAL, dma_mask);

	if (*dma_addr == DMA_MAPPING_ERROR)
		goto out_free;

	return page_address(page);

out_free:

	if (!dma_release_from_contiguous(dev, page, size >> PAGE_SHIFT))
		__free_pages(page, get_order(size));

	return NULL;
}