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
struct aq_rxpage {unsigned int order; scalar_t__ pg_off; int /*<<< orphan*/  daddr; struct page* page; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 struct page* dev_alloc_pages (unsigned int) ; 
 int /*<<< orphan*/  dma_map_page (struct device*,struct page*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aq_get_rxpage(struct aq_rxpage *rxpage, unsigned int order,
			 struct device *dev)
{
	struct page *page;
	dma_addr_t daddr;
	int ret = -ENOMEM;

	page = dev_alloc_pages(order);
	if (unlikely(!page))
		goto err_exit;

	daddr = dma_map_page(dev, page, 0, PAGE_SIZE << order,
			     DMA_FROM_DEVICE);

	if (unlikely(dma_mapping_error(dev, daddr)))
		goto free_page;

	rxpage->page = page;
	rxpage->daddr = daddr;
	rxpage->order = order;
	rxpage->pg_off = 0;

	return 0;

free_page:
	__free_pages(page, order);

err_exit:
	return ret;
}