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
struct ftgmac100 {scalar_t__ aneg_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftgmac100_config_pause (struct ftgmac100*) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_set_asym_pause (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftgmac100_set_pauseparam(struct net_device *netdev,
				    struct ethtool_pauseparam *pause)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;

	priv->aneg_pause = pause->autoneg;
	priv->tx_pause = pause->tx_pause;
	priv->rx_pause = pause->rx_pause;

	if (phydev)
		phy_set_asym_pause(phydev, pause->rx_pause, pause->tx_pause);

	if (netif_running(netdev)) {
		if (!(phydev && priv->aneg_pause))
			ftgmac100_config_pause(priv);
	}

	return 0;
}