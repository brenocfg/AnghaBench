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
struct mac_device {int /*<<< orphan*/  tx_pause_active; int /*<<< orphan*/  rx_pause_active; int /*<<< orphan*/  autoneg_pause; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  autoneg; } ;
struct dpaa_priv {struct mac_device* mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void dpaa_get_pauseparam(struct net_device *net_dev,
				struct ethtool_pauseparam *epause)
{
	struct mac_device *mac_dev;
	struct dpaa_priv *priv;

	priv = netdev_priv(net_dev);
	mac_dev = priv->mac_dev;

	if (!net_dev->phydev) {
		netdev_err(net_dev, "phy device not initialized\n");
		return;
	}

	epause->autoneg = mac_dev->autoneg_pause;
	epause->rx_pause = mac_dev->rx_pause_active;
	epause->tx_pause = mac_dev->tx_pause_active;
}