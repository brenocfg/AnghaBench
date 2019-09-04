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
struct sk_buff {int dummy; } ;
struct ixgbe_rx_buffer {scalar_t__ dma; int /*<<< orphan*/ * skb; int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; } ;
struct ixgbe_ring {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ dma; int page_released; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
 TYPE_1__* IXGBE_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IXGBE_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_can_reuse_rx_page (struct ixgbe_rx_buffer*) ; 
 int /*<<< orphan*/  ixgbe_reuse_rx_page (struct ixgbe_ring*,struct ixgbe_rx_buffer*) ; 
 int /*<<< orphan*/  ixgbe_rx_pg_size (struct ixgbe_ring*) ; 

__attribute__((used)) static void ixgbe_put_rx_buffer(struct ixgbe_ring *rx_ring,
				struct ixgbe_rx_buffer *rx_buffer,
				struct sk_buff *skb)
{
	if (ixgbe_can_reuse_rx_page(rx_buffer)) {
		/* hand second half of page back to the ring */
		ixgbe_reuse_rx_page(rx_ring, rx_buffer);
	} else {
		if (!IS_ERR(skb) && IXGBE_CB(skb)->dma == rx_buffer->dma) {
			/* the page has been released from the ring */
			IXGBE_CB(skb)->page_released = true;
		} else {
			/* we are not reusing the buffer so unmap it */
			dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
					     ixgbe_rx_pg_size(rx_ring),
					     DMA_FROM_DEVICE,
					     IXGBE_RX_DMA_ATTR);
		}
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	}

	/* clear contents of rx_buffer */
	rx_buffer->page = NULL;
	rx_buffer->skb = NULL;
}