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
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; } ;
struct TYPE_2__ {int /*<<< orphan*/  fc_autoneg; } ;
struct be_adapter {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cmd_get_flow_control (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
be_get_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *ecmd)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	be_cmd_get_flow_control(adapter, &ecmd->tx_pause, &ecmd->rx_pause);
	ecmd->autoneg = adapter->phy.fc_autoneg;
}