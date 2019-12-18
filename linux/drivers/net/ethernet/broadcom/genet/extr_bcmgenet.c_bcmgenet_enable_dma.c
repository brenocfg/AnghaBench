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
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL ; 
 int /*<<< orphan*/  bcmgenet_rdma_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_rdma_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_tdma_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_tdma_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcmgenet_enable_dma(struct bcmgenet_priv *priv, u32 dma_ctrl)
{
	u32 reg;

	reg = bcmgenet_rdma_readl(priv, DMA_CTRL);
	reg |= dma_ctrl;
	bcmgenet_rdma_writel(priv, reg, DMA_CTRL);

	reg = bcmgenet_tdma_readl(priv, DMA_CTRL);
	reg |= dma_ctrl;
	bcmgenet_tdma_writel(priv, reg, DMA_CTRL);
}