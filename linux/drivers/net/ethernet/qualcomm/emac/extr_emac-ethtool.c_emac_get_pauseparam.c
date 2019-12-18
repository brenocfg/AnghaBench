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
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct emac_adapter {scalar_t__ tx_flow_control; scalar_t__ rx_flow_control; scalar_t__ automatic; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void emac_get_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pause)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	pause->autoneg = adpt->automatic ? AUTONEG_ENABLE : AUTONEG_DISABLE;
	pause->rx_pause = adpt->rx_flow_control ? 1 : 0;
	pause->tx_pause = adpt->tx_flow_control ? 1 : 0;
}