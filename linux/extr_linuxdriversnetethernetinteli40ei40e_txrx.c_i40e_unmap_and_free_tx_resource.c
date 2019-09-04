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
struct i40e_tx_buffer {int tx_flags; int /*<<< orphan*/ * skb; int /*<<< orphan*/ * next_to_watch; int /*<<< orphan*/  xdpf; int /*<<< orphan*/  raw_buf; } ;
struct i40e_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int I40E_TX_FLAGS_FD_SB ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ ring_is_xdp (struct i40e_ring*) ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_unmap_and_free_tx_resource(struct i40e_ring *ring,
					    struct i40e_tx_buffer *tx_buffer)
{
	if (tx_buffer->skb) {
		if (tx_buffer->tx_flags & I40E_TX_FLAGS_FD_SB)
			kfree(tx_buffer->raw_buf);
		else if (ring_is_xdp(ring))
			xdp_return_frame(tx_buffer->xdpf);
		else
			dev_kfree_skb_any(tx_buffer->skb);
		if (dma_unmap_len(tx_buffer, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buffer, dma),
					 dma_unmap_len(tx_buffer, len),
					 DMA_TO_DEVICE);
	} else if (dma_unmap_len(tx_buffer, len)) {
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buffer, dma),
			       dma_unmap_len(tx_buffer, len),
			       DMA_TO_DEVICE);
	}

	tx_buffer->next_to_watch = NULL;
	tx_buffer->skb = NULL;
	dma_unmap_len_set(tx_buffer, len, 0);
	/* tx_buffer must be completely set up in the transmit path */
}