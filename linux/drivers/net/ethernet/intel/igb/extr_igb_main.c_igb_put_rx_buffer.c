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
struct igb_rx_buffer {int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  dma; } ;
struct igb_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IGB_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ igb_can_reuse_rx_page (struct igb_rx_buffer*) ; 
 int /*<<< orphan*/  igb_reuse_rx_page (struct igb_ring*,struct igb_rx_buffer*) ; 
 int /*<<< orphan*/  igb_rx_pg_size (struct igb_ring*) ; 

__attribute__((used)) static void igb_put_rx_buffer(struct igb_ring *rx_ring,
			      struct igb_rx_buffer *rx_buffer)
{
	if (igb_can_reuse_rx_page(rx_buffer)) {
		/* hand second half of page back to the ring */
		igb_reuse_rx_page(rx_ring, rx_buffer);
	} else {
		/* We are not reusing the buffer so unmap it and free
		 * any references we are holding to it
		 */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     igb_rx_pg_size(rx_ring), DMA_FROM_DEVICE,
				     IGB_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	}

	/* clear contents of rx_buffer */
	rx_buffer->page = NULL;
}