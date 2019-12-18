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
struct igc_rx_buffer {int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  dma; } ;
struct igc_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IGC_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ igc_can_reuse_rx_page (struct igc_rx_buffer*) ; 
 int /*<<< orphan*/  igc_reuse_rx_page (struct igc_ring*,struct igc_rx_buffer*) ; 
 int /*<<< orphan*/  igc_rx_pg_size (struct igc_ring*) ; 

__attribute__((used)) static void igc_put_rx_buffer(struct igc_ring *rx_ring,
			      struct igc_rx_buffer *rx_buffer)
{
	if (igc_can_reuse_rx_page(rx_buffer)) {
		/* hand second half of page back to the ring */
		igc_reuse_rx_page(rx_ring, rx_buffer);
	} else {
		/* We are not reusing the buffer so unmap it and free
		 * any references we are holding to it
		 */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     igc_rx_pg_size(rx_ring), DMA_FROM_DEVICE,
				     IGC_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	}

	/* clear contents of rx_buffer */
	rx_buffer->page = NULL;
}