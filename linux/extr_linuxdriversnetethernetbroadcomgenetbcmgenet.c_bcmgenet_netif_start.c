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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int CMD_RX_EN ; 
 int CMD_TX_EN ; 
 int /*<<< orphan*/  bcmgenet_enable_rx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_enable_tx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_link_intr_enable (struct bcmgenet_priv*) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umac_enable_set (struct bcmgenet_priv*,int,int) ; 

__attribute__((used)) static void bcmgenet_netif_start(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);

	/* Start the network engine */
	bcmgenet_enable_rx_napi(priv);

	umac_enable_set(priv, CMD_TX_EN | CMD_RX_EN, true);

	bcmgenet_enable_tx_napi(priv);

	/* Monitor link interrupts now */
	bcmgenet_link_intr_enable(priv);

	phy_start(dev->phydev);
}