#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sxgbe_priv_data {int /*<<< orphan*/  sxgbe_clk; int /*<<< orphan*/  ioaddr; TYPE_3__* hw; int /*<<< orphan*/  napi; int /*<<< orphan*/  eee_ctrl_timer; scalar_t__ eee_enabled; } ;
struct net_device {scalar_t__ phydev; } ;
struct TYPE_6__ {TYPE_2__* mac; TYPE_1__* dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_rx ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_tx ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_rx ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop_tx ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_RX_QUEUES ; 
 int /*<<< orphan*/  SXGBE_TX_QUEUES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_dma_desc_resources (struct sxgbe_priv_data*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct sxgbe_priv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sxgbe_disable_mtl_engine (struct sxgbe_priv_data*) ; 
 int /*<<< orphan*/  sxgbe_tx_del_timer (struct sxgbe_priv_data*) ; 

__attribute__((used)) static int sxgbe_release(struct net_device *dev)
{
	struct sxgbe_priv_data *priv = netdev_priv(dev);

	if (priv->eee_enabled)
		del_timer_sync(&priv->eee_ctrl_timer);

	/* Stop and disconnect the PHY */
	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	netif_tx_stop_all_queues(dev);

	napi_disable(&priv->napi);

	/* delete TX timers */
	sxgbe_tx_del_timer(priv);

	/* Stop TX/RX DMA and clear the descriptors */
	priv->hw->dma->stop_tx(priv->ioaddr, SXGBE_TX_QUEUES);
	priv->hw->dma->stop_rx(priv->ioaddr, SXGBE_RX_QUEUES);

	/* disable MTL queue */
	sxgbe_disable_mtl_engine(priv);

	/* Release and free the Rx/Tx resources */
	free_dma_desc_resources(priv);

	/* Disable the MAC Rx/Tx */
	priv->hw->mac->enable_tx(priv->ioaddr, false);
	priv->hw->mac->enable_rx(priv->ioaddr, false);

	clk_disable_unprepare(priv->sxgbe_clk);

	return 0;
}