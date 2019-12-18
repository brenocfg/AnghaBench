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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct bcmgenet_priv {int old_link; int old_speed; int old_duplex; int old_pause; int /*<<< orphan*/  bcmgenet_irq_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RX_EN ; 
 int /*<<< orphan*/  CMD_TX_EN ; 
 int /*<<< orphan*/  bcmgenet_disable_rx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_disable_tx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_dma_teardown (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_fini_dma (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_intr_disable (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_tx_reclaim_all (struct net_device*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_enable_set (struct bcmgenet_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcmgenet_netif_stop(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);

	bcmgenet_disable_tx_napi(priv);
	netif_tx_disable(dev);

	/* Disable MAC receive */
	umac_enable_set(priv, CMD_RX_EN, false);

	bcmgenet_dma_teardown(priv);

	/* Disable MAC transmit. TX DMA disabled must be done before this */
	umac_enable_set(priv, CMD_TX_EN, false);

	phy_stop(dev->phydev);
	bcmgenet_disable_rx_napi(priv);
	bcmgenet_intr_disable(priv);

	/* Wait for pending work items to complete. Since interrupts are
	 * disabled no new work will be scheduled.
	 */
	cancel_work_sync(&priv->bcmgenet_irq_work);

	priv->old_link = -1;
	priv->old_speed = -1;
	priv->old_duplex = -1;
	priv->old_pause = -1;

	/* tx reclaim */
	bcmgenet_tx_reclaim_all(dev);
	bcmgenet_fini_dma(priv);
}