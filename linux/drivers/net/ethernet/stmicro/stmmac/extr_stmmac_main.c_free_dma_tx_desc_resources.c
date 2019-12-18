#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct stmmac_tx_queue {int /*<<< orphan*/  tx_skbuff; int /*<<< orphan*/  tx_skbuff_dma; int /*<<< orphan*/  dma_tx_phy; int /*<<< orphan*/  dma_etx; int /*<<< orphan*/  dma_tx; } ;
struct stmmac_priv {int /*<<< orphan*/  device; int /*<<< orphan*/  extend_desc; struct stmmac_tx_queue* tx_queue; TYPE_1__* plat; } ;
struct dma_extended_desc {int dummy; } ;
struct dma_desc {int dummy; } ;
struct TYPE_2__ {size_t tx_queues_to_use; } ;

/* Variables and functions */
 int DMA_TX_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_tx_skbufs (struct stmmac_priv*,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_dma_tx_desc_resources(struct stmmac_priv *priv)
{
	u32 tx_count = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Free TX queue resources */
	for (queue = 0; queue < tx_count; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		/* Release the DMA TX socket buffers */
		dma_free_tx_skbufs(priv, queue);

		/* Free DMA regions of consistent memory previously allocated */
		if (!priv->extend_desc)
			dma_free_coherent(priv->device,
					  DMA_TX_SIZE * sizeof(struct dma_desc),
					  tx_q->dma_tx, tx_q->dma_tx_phy);
		else
			dma_free_coherent(priv->device, DMA_TX_SIZE *
					  sizeof(struct dma_extended_desc),
					  tx_q->dma_etx, tx_q->dma_tx_phy);

		kfree(tx_q->tx_skbuff_dma);
		kfree(tx_q->tx_skbuff);
	}
}