#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ice_rx_buf {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_reuse_count; } ;
struct ice_ring {int /*<<< orphan*/  dev; TYPE_1__ rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ICE_RX_DMA_ATTR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ice_can_reuse_rx_page (struct ice_rx_buf*) ; 
 int /*<<< orphan*/  ice_reuse_rx_page (struct ice_ring*,struct ice_rx_buf*) ; 

__attribute__((used)) static void ice_put_rx_buf(struct ice_ring *rx_ring, struct ice_rx_buf *rx_buf)
{
	if (!rx_buf)
		return;

	if (ice_can_reuse_rx_page(rx_buf)) {
		/* hand second half of page back to the ring */
		ice_reuse_rx_page(rx_ring, rx_buf);
		rx_ring->rx_stats.page_reuse_count++;
	} else {
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page_attrs(rx_ring->dev, rx_buf->dma, PAGE_SIZE,
				     DMA_FROM_DEVICE, ICE_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buf->page, rx_buf->pagecnt_bias);
	}

	/* clear contents of buffer_info */
	rx_buf->page = NULL;
	rx_buf->skb = NULL;
}