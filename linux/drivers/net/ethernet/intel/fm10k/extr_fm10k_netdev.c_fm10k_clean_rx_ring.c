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
struct fm10k_rx_buffer {int /*<<< orphan*/ * page; int /*<<< orphan*/  dma; } ;
struct fm10k_ring {size_t count; unsigned long size; scalar_t__ next_to_use; scalar_t__ next_to_clean; scalar_t__ next_to_alloc; struct fm10k_rx_buffer* desc; struct fm10k_rx_buffer* rx_buffer; int /*<<< orphan*/  dev; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fm10k_rx_buffer*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void fm10k_clean_rx_ring(struct fm10k_ring *rx_ring)
{
	unsigned long size;
	u16 i;

	if (!rx_ring->rx_buffer)
		return;

	dev_kfree_skb(rx_ring->skb);
	rx_ring->skb = NULL;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rx_ring->count; i++) {
		struct fm10k_rx_buffer *buffer = &rx_ring->rx_buffer[i];
		/* clean-up will only set page pointer to NULL */
		if (!buffer->page)
			continue;

		dma_unmap_page(rx_ring->dev, buffer->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
		__free_page(buffer->page);

		buffer->page = NULL;
	}

	size = sizeof(struct fm10k_rx_buffer) * rx_ring->count;
	memset(rx_ring->rx_buffer, 0, size);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
}