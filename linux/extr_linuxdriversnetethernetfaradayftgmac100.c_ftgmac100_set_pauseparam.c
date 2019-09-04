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
struct phy_device {int /*<<< orphan*/  advertising; } ;
struct net_device {struct phy_device* phydev; } ;
struct ftgmac100 {scalar_t__ aneg_pause; scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_Asym_Pause ; 
 int /*<<< orphan*/  ADVERTISED_Pause ; 
 int /*<<< orphan*/  ftgmac100_config_pause (struct ftgmac100*) ; 
 struct ftgmac100* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

__attribute__((used)) static int ftgmac100_set_pauseparam(struct net_device *netdev,
				    struct ethtool_pauseparam *pause)
{
	struct ftgmac100 *priv = netdev_priv(netdev);
	struct phy_device *phydev = netdev->phydev;

	priv->aneg_pause = pause->autoneg;
	priv->tx_pause = pause->tx_pause;
	priv->rx_pause = pause->rx_pause;

	if (phydev) {
		phydev->advertising &= ~ADVERTISED_Pause;
		phydev->advertising &= ~ADVERTISED_Asym_Pause;

		if (pause->rx_pause) {
			phydev->advertising |= ADVERTISED_Pause;
			phydev->advertising |= ADVERTISED_Asym_Pause;
		}

		if (pause->tx_pause)
			phydev->advertising ^= ADVERTISED_Asym_Pause;
	}
	if (netif_running(netdev)) {
		if (phydev && priv->aneg_pause)
			phy_start_aneg(phydev);
		else
			ftgmac100_config_pause(priv);
	}

	return 0;
}