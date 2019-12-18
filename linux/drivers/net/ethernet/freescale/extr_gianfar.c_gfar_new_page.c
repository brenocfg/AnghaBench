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
struct gfar_rx_buff {scalar_t__ page_offset; struct page* page; int /*<<< orphan*/  dma; } ;
struct gfar_priv_rx_q {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* dev_alloc_page () ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool gfar_new_page(struct gfar_priv_rx_q *rxq, struct gfar_rx_buff *rxb)
{
	struct page *page;
	dma_addr_t addr;

	page = dev_alloc_page();
	if (unlikely(!page))
		return false;

	addr = dma_map_page(rxq->dev, page, 0, PAGE_SIZE, DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(rxq->dev, addr))) {
		__free_page(page);

		return false;
	}

	rxb->dma = addr;
	rxb->page = page;
	rxb->page_offset = 0;

	return true;
}