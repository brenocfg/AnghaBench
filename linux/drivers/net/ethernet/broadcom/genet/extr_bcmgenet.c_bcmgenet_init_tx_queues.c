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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bcmgenet_priv {TYPE_1__* hw_params; } ;
struct TYPE_2__ {int tx_queues; int tx_bds_per_q; } ;

/* Variables and functions */
 int DESC_INDEX ; 
 int DMA_ARBITER_SP ; 
 int /*<<< orphan*/  DMA_ARB_CTRL ; 
 int /*<<< orphan*/  DMA_CTRL ; 
 int DMA_EN ; 
 int /*<<< orphan*/  DMA_PRIORITY_0 ; 
 int /*<<< orphan*/  DMA_PRIORITY_1 ; 
 int /*<<< orphan*/  DMA_PRIORITY_2 ; 
 size_t DMA_PRIO_REG_INDEX (int) ; 
 int DMA_PRIO_REG_SHIFT (int) ; 
 int DMA_RING_BUF_EN_SHIFT ; 
 int /*<<< orphan*/  DMA_RING_CFG ; 
 int GENET_Q0_PRIORITY ; 
 int GENET_Q16_TX_BD_CNT ; 
 int TOTAL_DESC ; 
 int /*<<< orphan*/  bcmgenet_init_tx_ring (struct bcmgenet_priv*,int,int,int,int) ; 
 int bcmgenet_tdma_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_tdma_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void bcmgenet_init_tx_queues(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	u32 i, dma_enable;
	u32 dma_ctrl, ring_cfg;
	u32 dma_priority[3] = {0, 0, 0};

	dma_ctrl = bcmgenet_tdma_readl(priv, DMA_CTRL);
	dma_enable = dma_ctrl & DMA_EN;
	dma_ctrl &= ~DMA_EN;
	bcmgenet_tdma_writel(priv, dma_ctrl, DMA_CTRL);

	dma_ctrl = 0;
	ring_cfg = 0;

	/* Enable strict priority arbiter mode */
	bcmgenet_tdma_writel(priv, DMA_ARBITER_SP, DMA_ARB_CTRL);

	/* Initialize Tx priority queues */
	for (i = 0; i < priv->hw_params->tx_queues; i++) {
		bcmgenet_init_tx_ring(priv, i, priv->hw_params->tx_bds_per_q,
				      i * priv->hw_params->tx_bds_per_q,
				      (i + 1) * priv->hw_params->tx_bds_per_q);
		ring_cfg |= (1 << i);
		dma_ctrl |= (1 << (i + DMA_RING_BUF_EN_SHIFT));
		dma_priority[DMA_PRIO_REG_INDEX(i)] |=
			((GENET_Q0_PRIORITY + i) << DMA_PRIO_REG_SHIFT(i));
	}

	/* Initialize Tx default queue 16 */
	bcmgenet_init_tx_ring(priv, DESC_INDEX, GENET_Q16_TX_BD_CNT,
			      priv->hw_params->tx_queues *
			      priv->hw_params->tx_bds_per_q,
			      TOTAL_DESC);
	ring_cfg |= (1 << DESC_INDEX);
	dma_ctrl |= (1 << (DESC_INDEX + DMA_RING_BUF_EN_SHIFT));
	dma_priority[DMA_PRIO_REG_INDEX(DESC_INDEX)] |=
		((GENET_Q0_PRIORITY + priv->hw_params->tx_queues) <<
		 DMA_PRIO_REG_SHIFT(DESC_INDEX));

	/* Set Tx queue priorities */
	bcmgenet_tdma_writel(priv, dma_priority[0], DMA_PRIORITY_0);
	bcmgenet_tdma_writel(priv, dma_priority[1], DMA_PRIORITY_1);
	bcmgenet_tdma_writel(priv, dma_priority[2], DMA_PRIORITY_2);

	/* Enable Tx queues */
	bcmgenet_tdma_writel(priv, ring_cfg, DMA_RING_CFG);

	/* Enable Tx DMA */
	if (dma_enable)
		dma_ctrl |= DMA_EN;
	bcmgenet_tdma_writel(priv, dma_ctrl, DMA_CTRL);
}