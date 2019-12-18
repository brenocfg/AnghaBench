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
struct net_device {scalar_t__ phydev; } ;
struct altera_tse_private {TYPE_1__* dmaops; int /*<<< orphan*/  mac_cfg_lock; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  rxdma_irq_lock; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uninit_dma ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* reset_dma ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* disable_txirq ) (struct altera_tse_private*) ;int /*<<< orphan*/  (* disable_rxirq ) (struct altera_tse_private*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_skbufs (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int reset_mac (struct altera_tse_private*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub2 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub3 (struct altera_tse_private*) ; 
 int /*<<< orphan*/  stub4 (struct altera_tse_private*) ; 

__attribute__((used)) static int tse_shutdown(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	int ret;
	unsigned long int flags;

	/* Stop the PHY */
	if (dev->phydev)
		phy_stop(dev->phydev);

	netif_stop_queue(dev);
	napi_disable(&priv->napi);

	/* Disable DMA interrupts */
	spin_lock_irqsave(&priv->rxdma_irq_lock, flags);
	priv->dmaops->disable_rxirq(priv);
	priv->dmaops->disable_txirq(priv);
	spin_unlock_irqrestore(&priv->rxdma_irq_lock, flags);

	/* Free the IRQ lines */
	free_irq(priv->rx_irq, dev);
	free_irq(priv->tx_irq, dev);

	/* disable and reset the MAC, empties fifo */
	spin_lock(&priv->mac_cfg_lock);
	spin_lock(&priv->tx_lock);

	ret = reset_mac(priv);
	/* Note that reset_mac will fail if the clocks are gated by the PHY
	 * due to the PHY being put into isolation or power down mode.
	 * This is not an error if reset fails due to no clock.
	 */
	if (ret)
		netdev_dbg(dev, "Cannot reset MAC core (error: %d)\n", ret);
	priv->dmaops->reset_dma(priv);
	free_skbufs(dev);

	spin_unlock(&priv->tx_lock);
	spin_unlock(&priv->mac_cfg_lock);

	priv->dmaops->uninit_dma(priv);

	return 0;
}