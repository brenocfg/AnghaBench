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
struct fm10k_rx_buffer {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; } ;
struct fm10k_ring {size_t next_to_alloc; size_t count; int /*<<< orphan*/  dev; struct fm10k_rx_buffer* rx_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FM10K_RX_BUFSZ ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_reuse_rx_page(struct fm10k_ring *rx_ring,
				struct fm10k_rx_buffer *old_buff)
{
	struct fm10k_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	*new_buff = *old_buff;

	/* sync the buffer for use by the device */
	dma_sync_single_range_for_device(rx_ring->dev, old_buff->dma,
					 old_buff->page_offset,
					 FM10K_RX_BUFSZ,
					 DMA_FROM_DEVICE);
}