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
typedef  size_t u16 ;
struct ice_rx_buf {scalar_t__ page_offset; int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; int /*<<< orphan*/ * skb; } ;
struct ice_ring {size_t count; unsigned long size; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ next_to_alloc; struct ice_rx_buf* desc; struct ice_rx_buf* rx_buf; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ice_rx_buf*,int /*<<< orphan*/ ,unsigned long) ; 

void ice_clean_rx_ring(struct ice_ring *rx_ring)
{
	struct device *dev = rx_ring->dev;
	unsigned long size;
	u16 i;

	/* ring already cleared, nothing to do */
	if (!rx_ring->rx_buf)
		return;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rx_ring->count; i++) {
		struct ice_rx_buf *rx_buf = &rx_ring->rx_buf[i];

		if (rx_buf->skb) {
			dev_kfree_skb(rx_buf->skb);
			rx_buf->skb = NULL;
		}
		if (!rx_buf->page)
			continue;

		dma_unmap_page(dev, rx_buf->dma, PAGE_SIZE, DMA_FROM_DEVICE);
		__free_pages(rx_buf->page, 0);

		rx_buf->page = NULL;
		rx_buf->page_offset = 0;
	}

	size = sizeof(struct ice_rx_buf) * rx_ring->count;
	memset(rx_ring->rx_buf, 0, size);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
}