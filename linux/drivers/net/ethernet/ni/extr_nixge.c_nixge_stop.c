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
struct nixge_priv {int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  dma_err_tasklet; int /*<<< orphan*/  napi; } ;
struct net_device {scalar_t__ phydev; } ;

/* Variables and functions */
 int XAXIDMA_CR_RUNSTOP_MASK ; 
 int /*<<< orphan*/  XAXIDMA_RX_CR_OFFSET ; 
 int /*<<< orphan*/  XAXIDMA_TX_CR_OFFSET ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct nixge_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int nixge_dma_read_reg (struct nixge_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nixge_dma_write_reg (struct nixge_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nixge_hw_dma_bd_release (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nixge_stop(struct net_device *ndev)
{
	struct nixge_priv *priv = netdev_priv(ndev);
	u32 cr;

	netif_stop_queue(ndev);
	napi_disable(&priv->napi);

	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	}

	cr = nixge_dma_read_reg(priv, XAXIDMA_RX_CR_OFFSET);
	nixge_dma_write_reg(priv, XAXIDMA_RX_CR_OFFSET,
			    cr & (~XAXIDMA_CR_RUNSTOP_MASK));
	cr = nixge_dma_read_reg(priv, XAXIDMA_TX_CR_OFFSET);
	nixge_dma_write_reg(priv, XAXIDMA_TX_CR_OFFSET,
			    cr & (~XAXIDMA_CR_RUNSTOP_MASK));

	tasklet_kill(&priv->dma_err_tasklet);

	free_irq(priv->tx_irq, ndev);
	free_irq(priv->rx_irq, ndev);

	nixge_hw_dma_bd_release(ndev);

	return 0;
}