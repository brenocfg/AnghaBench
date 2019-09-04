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
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct nb8800_priv {int /*<<< orphan*/  pause_aneg; int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  nb8800_pause_adv (struct net_device*) ; 
 int /*<<< orphan*/  nb8800_pause_config (struct net_device*) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int nb8800_set_pauseparam(struct net_device *dev,
				 struct ethtool_pauseparam *pp)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;

	priv->pause_aneg = pp->autoneg;
	priv->pause_rx = pp->rx_pause;
	priv->pause_tx = pp->tx_pause;

	nb8800_pause_adv(dev);

	if (!priv->pause_aneg)
		nb8800_pause_config(dev);
	else if (phydev)
		phy_start_aneg(phydev);

	return 0;
}