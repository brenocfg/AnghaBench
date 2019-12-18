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
struct igb_rx_buffer {int /*<<< orphan*/  pagecnt_bias; int /*<<< orphan*/  page; int /*<<< orphan*/  dma; int /*<<< orphan*/  page_offset; } ;
struct igb_ring {size_t next_to_clean; size_t next_to_alloc; size_t count; scalar_t__ next_to_use; int /*<<< orphan*/  dev; struct igb_rx_buffer* rx_buffer_info; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IGB_RX_DMA_ATTR ; 
 int /*<<< orphan*/  __page_frag_cache_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_rx_bufsz (struct igb_ring*) ; 
 int /*<<< orphan*/  igb_rx_pg_size (struct igb_ring*) ; 

__attribute__((used)) static void igb_clean_rx_ring(struct igb_ring *rx_ring)
{
	u16 i = rx_ring->next_to_clean;

	dev_kfree_skb(rx_ring->skb);
	rx_ring->skb = NULL;

	/* Free all the Rx ring sk_buffs */
	while (i != rx_ring->next_to_alloc) {
		struct igb_rx_buffer *buffer_info = &rx_ring->rx_buffer_info[i];

		/* Invalidate cache lines that may have been written to by
		 * device so that we avoid corrupting memory.
		 */
		dma_sync_single_range_for_cpu(rx_ring->dev,
					      buffer_info->dma,
					      buffer_info->page_offset,
					      igb_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);

		/* free resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev,
				     buffer_info->dma,
				     igb_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IGB_RX_DMA_ATTR);
		__page_frag_cache_drain(buffer_info->page,
					buffer_info->pagecnt_bias);

		i++;
		if (i == rx_ring->count)
			i = 0;
	}

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
}