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
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct emac_adapter {int automatic; int rx_flow_control; int tx_flow_control; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int emac_reinit_locked (struct emac_adapter*) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int emac_set_pauseparam(struct net_device *netdev,
			       struct ethtool_pauseparam *pause)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	adpt->automatic = pause->autoneg == AUTONEG_ENABLE;
	adpt->rx_flow_control = pause->rx_pause != 0;
	adpt->tx_flow_control = pause->tx_pause != 0;

	if (netif_running(netdev))
		return emac_reinit_locked(adpt);

	return 0;
}