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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ixgb_adapter {int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {scalar_t__ speed; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  ixgb_down (struct ixgb_adapter*,int) ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_set_speed_duplex (struct net_device*) ; 
 int /*<<< orphan*/  ixgb_up (struct ixgb_adapter*) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgb_set_link_ksettings(struct net_device *netdev,
			const struct ethtool_link_ksettings *cmd)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	u32 speed = cmd->base.speed;

	if (cmd->base.autoneg == AUTONEG_ENABLE ||
	    (speed + cmd->base.duplex != SPEED_10000 + DUPLEX_FULL))
		return -EINVAL;

	if (netif_running(adapter->netdev)) {
		ixgb_down(adapter, true);
		ixgb_reset(adapter);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	} else
		ixgb_reset(adapter);

	return 0;
}