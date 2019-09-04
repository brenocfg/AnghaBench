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
typedef  int u32 ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int DESC_INDEX ; 
 int /*<<< orphan*/  DMA_CTRL ; 
 int DMA_EN ; 
 int DMA_RING_BUF_EN_SHIFT ; 
 int /*<<< orphan*/  UMAC_TX_FLUSH ; 
 int bcmgenet_rdma_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_rdma_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int bcmgenet_tdma_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_tdma_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u32 bcmgenet_dma_disable(struct bcmgenet_priv *priv)
{
	u32 reg;
	u32 dma_ctrl;

	/* disable DMA */
	dma_ctrl = 1 << (DESC_INDEX + DMA_RING_BUF_EN_SHIFT) | DMA_EN;
	reg = bcmgenet_tdma_readl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_tdma_writel(priv, reg, DMA_CTRL);

	reg = bcmgenet_rdma_readl(priv, DMA_CTRL);
	reg &= ~dma_ctrl;
	bcmgenet_rdma_writel(priv, reg, DMA_CTRL);

	bcmgenet_umac_writel(priv, 1, UMAC_TX_FLUSH);
	udelay(10);
	bcmgenet_umac_writel(priv, 0, UMAC_TX_FLUSH);

	return dma_ctrl;
}