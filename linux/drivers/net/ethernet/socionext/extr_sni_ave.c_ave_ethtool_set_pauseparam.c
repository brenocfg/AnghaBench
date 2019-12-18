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
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;
struct ave_private {int /*<<< orphan*/  pause_tx; int /*<<< orphan*/  pause_rx; int /*<<< orphan*/  pause_auto; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_set_asym_pause (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ave_ethtool_set_pauseparam(struct net_device *ndev,
				      struct ethtool_pauseparam *pause)
{
	struct ave_private *priv = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (!phydev)
		return -EINVAL;

	priv->pause_auto = pause->autoneg;
	priv->pause_rx   = pause->rx_pause;
	priv->pause_tx   = pause->tx_pause;

	phy_set_asym_pause(phydev, pause->rx_pause, pause->tx_pause);

	return 0;
}