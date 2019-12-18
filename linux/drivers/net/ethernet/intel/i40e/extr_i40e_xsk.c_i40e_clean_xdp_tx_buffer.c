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
struct i40e_tx_buffer {int /*<<< orphan*/  xdpf; } ;
struct i40e_ring {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_clean_xdp_tx_buffer(struct i40e_ring *tx_ring,
				     struct i40e_tx_buffer *tx_bi)
{
	xdp_return_frame(tx_bi->xdpf);
	dma_unmap_single(tx_ring->dev,
			 dma_unmap_addr(tx_bi, dma),
			 dma_unmap_len(tx_bi, len), DMA_TO_DEVICE);
	dma_unmap_len_set(tx_bi, len, 0);
}