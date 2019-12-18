#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct stmmac_priv {scalar_t__ wol_irq; scalar_t__ lpi_irq; int /*<<< orphan*/  ioaddr; TYPE_2__* tx_queue; TYPE_1__* plat; int /*<<< orphan*/  phylink; int /*<<< orphan*/  eee_ctrl_timer; scalar_t__ eee_enabled; } ;
struct net_device {scalar_t__ irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  txtimer; } ;
struct TYPE_3__ {size_t tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_dma_desc_resources (struct stmmac_priv*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_disable_all_queues (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mac_set (struct stmmac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stmmac_release_ptp (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_stop_all_dma (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_stop_all_queues (struct stmmac_priv*) ; 

__attribute__((used)) static int stmmac_release(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	u32 chan;

	if (priv->eee_enabled)
		del_timer_sync(&priv->eee_ctrl_timer);

	/* Stop and disconnect the PHY */
	phylink_stop(priv->phylink);
	phylink_disconnect_phy(priv->phylink);

	stmmac_stop_all_queues(priv);

	stmmac_disable_all_queues(priv);

	for (chan = 0; chan < priv->plat->tx_queues_to_use; chan++)
		del_timer_sync(&priv->tx_queue[chan].txtimer);

	/* Free the IRQ lines */
	free_irq(dev->irq, dev);
	if (priv->wol_irq != dev->irq)
		free_irq(priv->wol_irq, dev);
	if (priv->lpi_irq > 0)
		free_irq(priv->lpi_irq, dev);

	/* Stop TX/RX DMA and clear the descriptors */
	stmmac_stop_all_dma(priv);

	/* Release and free the Rx/Tx resources */
	free_dma_desc_resources(priv);

	/* Disable the MAC Rx/Tx */
	stmmac_mac_set(priv, priv->ioaddr, false);

	netif_carrier_off(dev);

	stmmac_release_ptp(priv);

	return 0;
}