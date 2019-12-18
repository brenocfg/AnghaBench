#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  pause_autoneg; } ;
struct xgbe_prv_data {TYPE_1__ phy; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xgbe_get_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pause)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);

	pause->autoneg = pdata->phy.pause_autoneg;
	pause->tx_pause = pdata->phy.tx_pause;
	pause->rx_pause = pdata->phy.rx_pause;
}