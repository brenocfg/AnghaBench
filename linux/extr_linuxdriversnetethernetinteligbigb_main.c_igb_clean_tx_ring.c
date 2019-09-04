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
typedef  union e1000_adv_tx_desc {int dummy; } e1000_adv_tx_desc ;
typedef  size_t u16 ;
struct igb_tx_buffer {union e1000_adv_tx_desc* next_to_watch; int /*<<< orphan*/  skb; } ;
struct igb_ring {size_t next_to_clean; size_t next_to_use; size_t count; struct igb_tx_buffer* tx_buffer_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 union e1000_adv_tx_desc* IGB_TX_DESC (struct igb_ring*,size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct igb_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct igb_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct igb_ring*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void igb_clean_tx_ring(struct igb_ring *tx_ring)
{
	u16 i = tx_ring->next_to_clean;
	struct igb_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	while (i != tx_ring->next_to_use) {
		union e1000_adv_tx_desc *eop_desc, *tx_desc;

		/* Free all the Tx ring sk_buffs */
		dev_kfree_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check for eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IGB_TX_DESC(tx_ring, i);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buffer++;
			tx_desc++;
			i++;
			if (unlikely(i == tx_ring->count)) {
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGB_TX_DESC(tx_ring, 0);
			}

			/* unmap any remaining paged data */
			if (dma_unmap_len(tx_buffer, len))
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
		}

		/* move us one more past the eop_desc for start of next pkt */
		tx_buffer++;
		i++;
		if (unlikely(i == tx_ring->count)) {
			i = 0;
			tx_buffer = tx_ring->tx_buffer_info;
		}
	}

	/* reset BQL for queue */
	netdev_tx_reset_queue(txring_txq(tx_ring));

	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
}