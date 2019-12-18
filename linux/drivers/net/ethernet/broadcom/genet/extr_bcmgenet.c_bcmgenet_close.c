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
struct bcmgenet_priv {int /*<<< orphan*/  clk; scalar_t__ internal_phy; int /*<<< orphan*/  irq1; int /*<<< orphan*/  irq0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENET_POWER_PASSIVE ; 
 int /*<<< orphan*/  bcmgenet_netif_stop (struct net_device*) ; 
 int bcmgenet_power_down (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  ifdown ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct bcmgenet_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcmgenet_close(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	int ret = 0;

	netif_dbg(priv, ifdown, dev, "bcmgenet_close\n");

	bcmgenet_netif_stop(dev);

	/* Really kill the PHY state machine and disconnect from it */
	phy_disconnect(dev->phydev);

	free_irq(priv->irq0, priv);
	free_irq(priv->irq1, priv);

	if (priv->internal_phy)
		ret = bcmgenet_power_down(priv, GENET_POWER_PASSIVE);

	clk_disable_unprepare(priv->clk);

	return ret;
}