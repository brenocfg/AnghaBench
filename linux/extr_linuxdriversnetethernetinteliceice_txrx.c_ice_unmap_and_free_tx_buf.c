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
struct ice_tx_buf {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * next_to_watch; } ;
struct ice_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ice_tx_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct ice_tx_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ice_tx_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 

__attribute__((used)) static void
ice_unmap_and_free_tx_buf(struct ice_ring *ring, struct ice_tx_buf *tx_buf)
{
	if (tx_buf->skb) {
		dev_kfree_skb_any(tx_buf->skb);
		if (dma_unmap_len(tx_buf, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buf, dma),
					 dma_unmap_len(tx_buf, len),
					 DMA_TO_DEVICE);
	} else if (dma_unmap_len(tx_buf, len)) {
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buf, dma),
			       dma_unmap_len(tx_buf, len),
			       DMA_TO_DEVICE);
	}

	tx_buf->next_to_watch = NULL;
	tx_buf->skb = NULL;
	dma_unmap_len_set(tx_buf, len, 0);
	/* tx_buf must be completely set up in the transmit path */
}