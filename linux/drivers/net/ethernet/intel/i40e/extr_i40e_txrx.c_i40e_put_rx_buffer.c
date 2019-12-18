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
struct i40e_rx_buffer {int /*<<< orphan*/ * page; int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  dma; } ;
struct i40e_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  I40E_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_can_reuse_rx_page (struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  i40e_reuse_rx_page (struct i40e_ring*,struct i40e_rx_buffer*) ; 
 int /*<<< orphan*/  i40e_rx_pg_size (struct i40e_ring*) ; 

__attribute__((used)) static void i40e_put_rx_buffer(struct i40e_ring *rx_ring,
			       struct i40e_rx_buffer *rx_buffer)
{
	if (i40e_can_reuse_rx_page(rx_buffer)) {
		/* hand second half of page back to the ring */
		i40e_reuse_rx_page(rx_ring, rx_buffer);
	} else {
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
				     i40e_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE, I40E_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
		/* clear contents of buffer_info */
		rx_buffer->page = NULL;
	}
}