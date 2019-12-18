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
struct ice_rx_buf {scalar_t__ page_offset; int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  dma; int /*<<< orphan*/ * skb; } ;
struct ice_ring {size_t count; int size; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ next_to_alloc; struct ice_rx_buf* desc; struct ice_rx_buf* rx_buf; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ICE_RXBUF_2048 ; 
 int /*<<< orphan*/  ICE_RX_DMA_ATTR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ice_rx_buf*,int /*<<< orphan*/ ,int) ; 

void ice_clean_rx_ring(struct ice_ring *rx_ring)
{
	struct device *dev = rx_ring->dev;
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

		/* Invalidate cache lines that may have been written to by
		 * device so that we avoid corrupting memory.
		 */
		dma_sync_single_range_for_cpu(dev, rx_buf->dma,
					      rx_buf->page_offset,
					      ICE_RXBUF_2048, DMA_FROM_DEVICE);

		/* free resources associated with mapping */
		dma_unmap_page_attrs(dev, rx_buf->dma, PAGE_SIZE,
				     DMA_FROM_DEVICE, ICE_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buf->page, rx_buf->pagecnt_bias);

		rx_buf->page = NULL;
		rx_buf->page_offset = 0;
	}

	memset(rx_ring->rx_buf, 0, sizeof(*rx_ring->rx_buf) * rx_ring->count);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
}