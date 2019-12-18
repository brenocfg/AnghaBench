#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct atl1c_hw {scalar_t__ autoneg_advertised; } ;
struct atl1c_adapter {int /*<<< orphan*/  flags; TYPE_2__* pdev; struct atl1c_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_1000baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_10baseT_Full ; 
 scalar_t__ ADVERTISED_10baseT_Half ; 
 scalar_t__ ADVERTISED_Autoneg ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 scalar_t__ atl1c_restart_autoneg (struct atl1c_hw*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct atl1c_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct atl1c_adapter*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1c_set_link_ksettings(struct net_device *netdev,
				    const struct ethtool_link_ksettings *cmd)
{
	struct atl1c_adapter *adapter = netdev_priv(netdev);
	struct atl1c_hw *hw = &adapter->hw;
	u16  autoneg_advertised;

	while (test_and_set_bit(__AT_RESETTING, &adapter->flags))
		msleep(1);

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		autoneg_advertised = ADVERTISED_Autoneg;
	} else {
		u32 speed = cmd->base.speed;
		if (speed == SPEED_1000) {
			if (cmd->base.duplex != DUPLEX_FULL) {
				if (netif_msg_link(adapter))
					dev_warn(&adapter->pdev->dev,
						"1000M half is invalid\n");
				clear_bit(__AT_RESETTING, &adapter->flags);
				return -EINVAL;
			}
			autoneg_advertised = ADVERTISED_1000baseT_Full;
		} else if (speed == SPEED_100) {
			if (cmd->base.duplex == DUPLEX_FULL)
				autoneg_advertised = ADVERTISED_100baseT_Full;
			else
				autoneg_advertised = ADVERTISED_100baseT_Half;
		} else {
			if (cmd->base.duplex == DUPLEX_FULL)
				autoneg_advertised = ADVERTISED_10baseT_Full;
			else
				autoneg_advertised = ADVERTISED_10baseT_Half;
		}
	}

	if (hw->autoneg_advertised != autoneg_advertised) {
		hw->autoneg_advertised = autoneg_advertised;
		if (atl1c_restart_autoneg(hw) != 0) {
			if (netif_msg_link(adapter))
				dev_warn(&adapter->pdev->dev,
					"ethtool speed/duplex setting failed\n");
			clear_bit(__AT_RESETTING, &adapter->flags);
			return -EINVAL;
		}
	}
	clear_bit(__AT_RESETTING, &adapter->flags);
	return 0;
}