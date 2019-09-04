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
typedef  unsigned int u32 ;
struct bcmgenet_tx_ring {unsigned int index; unsigned int queue; unsigned int size; unsigned int clean_ptr; unsigned int free_bds; unsigned int write_ptr; unsigned int cb_ptr; unsigned int end_ptr; int /*<<< orphan*/  napi; scalar_t__ prod_index; scalar_t__ c_index; scalar_t__ cbs; int /*<<< orphan*/  int_disable; int /*<<< orphan*/  int_enable; struct bcmgenet_priv* priv; int /*<<< orphan*/  lock; } ;
struct bcmgenet_priv {int /*<<< orphan*/  dev; scalar_t__ tx_cbs; struct bcmgenet_tx_ring* tx_rings; } ;

/* Variables and functions */
 unsigned int DESC_INDEX ; 
 int /*<<< orphan*/  DMA_END_ADDR ; 
 int /*<<< orphan*/  DMA_MBUF_DONE_THRESH ; 
 int /*<<< orphan*/  DMA_RING_BUF_SIZE ; 
 unsigned int DMA_RING_SIZE_SHIFT ; 
 int /*<<< orphan*/  DMA_START_ADDR ; 
 int ENET_MAX_MTU_SIZE ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 unsigned int RX_BUF_LENGTH ; 
 int /*<<< orphan*/  TDMA_CONS_INDEX ; 
 int /*<<< orphan*/  TDMA_FLOW_PERIOD ; 
 int /*<<< orphan*/  TDMA_PROD_INDEX ; 
 int /*<<< orphan*/  TDMA_READ_PTR ; 
 int /*<<< orphan*/  TDMA_WRITE_PTR ; 
 unsigned int WORDS_PER_BD (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_tdma_ring_writel (struct bcmgenet_priv*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_tx_poll ; 
 int /*<<< orphan*/  bcmgenet_tx_ring16_int_disable ; 
 int /*<<< orphan*/  bcmgenet_tx_ring16_int_enable ; 
 int /*<<< orphan*/  bcmgenet_tx_ring_int_disable ; 
 int /*<<< orphan*/  bcmgenet_tx_ring_int_enable ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcmgenet_init_tx_ring(struct bcmgenet_priv *priv,
				  unsigned int index, unsigned int size,
				  unsigned int start_ptr, unsigned int end_ptr)
{
	struct bcmgenet_tx_ring *ring = &priv->tx_rings[index];
	u32 words_per_bd = WORDS_PER_BD(priv);
	u32 flow_period_val = 0;

	spin_lock_init(&ring->lock);
	ring->priv = priv;
	ring->index = index;
	if (index == DESC_INDEX) {
		ring->queue = 0;
		ring->int_enable = bcmgenet_tx_ring16_int_enable;
		ring->int_disable = bcmgenet_tx_ring16_int_disable;
	} else {
		ring->queue = index + 1;
		ring->int_enable = bcmgenet_tx_ring_int_enable;
		ring->int_disable = bcmgenet_tx_ring_int_disable;
	}
	ring->cbs = priv->tx_cbs + start_ptr;
	ring->size = size;
	ring->clean_ptr = start_ptr;
	ring->c_index = 0;
	ring->free_bds = size;
	ring->write_ptr = start_ptr;
	ring->cb_ptr = start_ptr;
	ring->end_ptr = end_ptr - 1;
	ring->prod_index = 0;

	/* Set flow period for ring != 16 */
	if (index != DESC_INDEX)
		flow_period_val = ENET_MAX_MTU_SIZE << 16;

	bcmgenet_tdma_ring_writel(priv, index, 0, TDMA_PROD_INDEX);
	bcmgenet_tdma_ring_writel(priv, index, 0, TDMA_CONS_INDEX);
	bcmgenet_tdma_ring_writel(priv, index, 1, DMA_MBUF_DONE_THRESH);
	/* Disable rate control for now */
	bcmgenet_tdma_ring_writel(priv, index, flow_period_val,
				  TDMA_FLOW_PERIOD);
	bcmgenet_tdma_ring_writel(priv, index,
				  ((size << DMA_RING_SIZE_SHIFT) |
				   RX_BUF_LENGTH), DMA_RING_BUF_SIZE);

	/* Set start and end address, read and write pointers */
	bcmgenet_tdma_ring_writel(priv, index, start_ptr * words_per_bd,
				  DMA_START_ADDR);
	bcmgenet_tdma_ring_writel(priv, index, start_ptr * words_per_bd,
				  TDMA_READ_PTR);
	bcmgenet_tdma_ring_writel(priv, index, start_ptr * words_per_bd,
				  TDMA_WRITE_PTR);
	bcmgenet_tdma_ring_writel(priv, index, end_ptr * words_per_bd - 1,
				  DMA_END_ADDR);

	/* Initialize Tx NAPI */
	netif_napi_add(priv->dev, &ring->napi, bcmgenet_tx_poll,
		       NAPI_POLL_WEIGHT);
}