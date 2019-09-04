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
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_ORDER ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 unsigned int __fls (unsigned long) ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 int /*<<< orphan*/  __iommu_dma_free_pages (struct page**,unsigned int) ; 
 struct page* alloc_pages (int,unsigned int) ; 
 struct page** kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 
 struct page** vzalloc (unsigned int) ; 

__attribute__((used)) static struct page **__iommu_dma_alloc_pages(unsigned int count,
		unsigned long order_mask, gfp_t gfp)
{
	struct page **pages;
	unsigned int i = 0, array_size = count * sizeof(*pages);

	order_mask &= (2U << MAX_ORDER) - 1;
	if (!order_mask)
		return NULL;

	if (array_size <= PAGE_SIZE)
		pages = kzalloc(array_size, GFP_KERNEL);
	else
		pages = vzalloc(array_size);
	if (!pages)
		return NULL;

	/* IOMMU can map any pages, so himem can also be used here */
	gfp |= __GFP_NOWARN | __GFP_HIGHMEM;

	while (count) {
		struct page *page = NULL;
		unsigned int order_size;

		/*
		 * Higher-order allocations are a convenience rather
		 * than a necessity, hence using __GFP_NORETRY until
		 * falling back to minimum-order allocations.
		 */
		for (order_mask &= (2U << __fls(count)) - 1;
		     order_mask; order_mask &= ~order_size) {
			unsigned int order = __fls(order_mask);

			order_size = 1U << order;
			page = alloc_pages((order_mask - order_size) ?
					   gfp | __GFP_NORETRY : gfp, order);
			if (!page)
				continue;
			if (!order)
				break;
			if (!PageCompound(page)) {
				split_page(page, order);
				break;
			} else if (!split_huge_page(page)) {
				break;
			}
			__free_pages(page, order);
		}
		if (!page) {
			__iommu_dma_free_pages(pages, i);
			return NULL;
		}
		count -= order_size;
		while (order_size--)
			pages[i++] = page++;
	}
	return pages;
}