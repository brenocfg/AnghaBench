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
typedef  union ixgbe_adv_tx_desc {int dummy; } ixgbe_adv_tx_desc ;
typedef  size_t u16 ;
struct ixgbe_tx_buffer {union ixgbe_adv_tx_desc* next_to_watch; int /*<<< orphan*/  skb; int /*<<< orphan*/  xdpf; } ;
struct ixgbe_ring {size_t next_to_clean; size_t next_to_use; size_t count; struct ixgbe_tx_buffer* tx_buffer_info; int /*<<< orphan*/  dev; scalar_t__ xsk_umem; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 union ixgbe_adv_tx_desc* IXGBE_TX_DESC (struct ixgbe_ring*,size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_xsk_clean_tx_ring (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_is_xdp (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  txring_txq (struct ixgbe_ring*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_clean_tx_ring(struct ixgbe_ring *tx_ring)
{
	u16 i = tx_ring->next_to_clean;
	struct ixgbe_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	if (tx_ring->xsk_umem) {
		ixgbe_xsk_clean_tx_ring(tx_ring);
		goto out;
	}

	while (i != tx_ring->next_to_use) {
		union ixgbe_adv_tx_desc *eop_desc, *tx_desc;

		/* Free all the Tx ring sk_buffs */
		if (ring_is_xdp(tx_ring))
			xdp_return_frame(tx_buffer->xdpf);
		else
			dev_kfree_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check for eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IXGBE_TX_DESC(tx_ring, i);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buffer++;
			tx_desc++;
			i++;
			if (unlikely(i == tx_ring->count)) {
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBE_TX_DESC(tx_ring, 0);
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
	if (!ring_is_xdp(tx_ring))
		netdev_tx_reset_queue(txring_txq(tx_ring));

out:
	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
}