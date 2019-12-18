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
struct stmmac_tx_queue {scalar_t__ dma_tx; scalar_t__ dma_etx; } ;
struct stmmac_priv {scalar_t__ extend_desc; struct stmmac_tx_queue* tx_queue; TYPE_1__* plat; } ;
struct TYPE_2__ {size_t tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_SIZE ; 
 int /*<<< orphan*/  pr_info (char*,size_t) ; 
 int /*<<< orphan*/  stmmac_display_ring (struct stmmac_priv*,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stmmac_display_tx_rings(struct stmmac_priv *priv)
{
	u32 tx_cnt = priv->plat->tx_queues_to_use;
	void *head_tx;
	u32 queue;

	/* Display TX rings */
	for (queue = 0; queue < tx_cnt; queue++) {
		struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

		pr_info("\tTX Queue %d rings\n", queue);

		if (priv->extend_desc)
			head_tx = (void *)tx_q->dma_etx;
		else
			head_tx = (void *)tx_q->dma_tx;

		stmmac_display_ring(priv, head_tx, DMA_TX_SIZE, false);
	}
}