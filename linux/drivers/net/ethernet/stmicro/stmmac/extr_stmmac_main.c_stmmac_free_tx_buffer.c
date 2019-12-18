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
struct stmmac_tx_queue {TYPE_1__* tx_skbuff_dma; int /*<<< orphan*/ ** tx_skbuff; } ;
struct stmmac_priv {int /*<<< orphan*/  device; struct stmmac_tx_queue* tx_queue; } ;
struct TYPE_2__ {int map_as_page; scalar_t__ buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_free_tx_buffer(struct stmmac_priv *priv, u32 queue, int i)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

	if (tx_q->tx_skbuff_dma[i].buf) {
		if (tx_q->tx_skbuff_dma[i].map_as_page)
			dma_unmap_page(priv->device,
				       tx_q->tx_skbuff_dma[i].buf,
				       tx_q->tx_skbuff_dma[i].len,
				       DMA_TO_DEVICE);
		else
			dma_unmap_single(priv->device,
					 tx_q->tx_skbuff_dma[i].buf,
					 tx_q->tx_skbuff_dma[i].len,
					 DMA_TO_DEVICE);
	}

	if (tx_q->tx_skbuff[i]) {
		dev_kfree_skb_any(tx_q->tx_skbuff[i]);
		tx_q->tx_skbuff[i] = NULL;
		tx_q->tx_skbuff_dma[i].buf = 0;
		tx_q->tx_skbuff_dma[i].map_as_page = false;
	}
}