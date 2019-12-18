#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int (* setup_link ) (struct ixgbe_hw*,int,int) ;} ;
struct TYPE_9__ {int autotry_restart; TYPE_3__ ops; } ;
struct TYPE_7__ {scalar_t__ media_type; int autoneg_advertised; scalar_t__ multispeed_fiber; } ;
struct ixgbe_hw {TYPE_4__ mac; TYPE_2__ phy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;
struct TYPE_10__ {scalar_t__ autoneg; int speed; int duplex; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_5__ base; TYPE_1__ link_modes; } ;
typedef  int s32 ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_10baseT_Full ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int EINVAL ; 
 int IXGBE_LINK_SPEED_100_FULL ; 
 int IXGBE_LINK_SPEED_10GB_FULL ; 
 int IXGBE_LINK_SPEED_10_FULL ; 
 int IXGBE_LINK_SPEED_1GB_FULL ; 
 int SPEED_10000 ; 
 int /*<<< orphan*/  __IXGBE_IN_SFP_INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_media_type_copper ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  probe ; 
 int stub1 (struct ixgbe_hw*,int,int) ; 
 int stub2 (struct ixgbe_hw*,int,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ixgbe_set_link_ksettings(struct net_device *netdev,
				    const struct ethtool_link_ksettings *cmd)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 advertised, old;
	s32 err = 0;
	u32 supported, advertising;

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if ((hw->phy.media_type == ixgbe_media_type_copper) ||
	    (hw->phy.multispeed_fiber)) {
		/*
		 * this function does not support duplex forcing, but can
		 * limit the advertising of the adapter to the specified speed
		 */
		if (advertising & ~supported)
			return -EINVAL;

		/* only allow one speed at a time if no autoneg */
		if (!cmd->base.autoneg && hw->phy.multispeed_fiber) {
			if (advertising ==
			    (ADVERTISED_10000baseT_Full |
			     ADVERTISED_1000baseT_Full))
				return -EINVAL;
		}

		old = hw->phy.autoneg_advertised;
		advertised = 0;
		if (advertising & ADVERTISED_10000baseT_Full)
			advertised |= IXGBE_LINK_SPEED_10GB_FULL;

		if (advertising & ADVERTISED_1000baseT_Full)
			advertised |= IXGBE_LINK_SPEED_1GB_FULL;

		if (advertising & ADVERTISED_100baseT_Full)
			advertised |= IXGBE_LINK_SPEED_100_FULL;

		if (advertising & ADVERTISED_10baseT_Full)
			advertised |= IXGBE_LINK_SPEED_10_FULL;

		if (old == advertised)
			return err;
		/* this sets the link speed and restarts auto-neg */
		while (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
			usleep_range(1000, 2000);

		hw->mac.autotry_restart = true;
		err = hw->mac.ops.setup_link(hw, advertised, true);
		if (err) {
			e_info(probe, "setup link failed with code %d\n", err);
			hw->mac.ops.setup_link(hw, old, true);
		}
		clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);
	} else {
		/* in this case we currently only support 10Gb/FULL */
		u32 speed = cmd->base.speed;

		if ((cmd->base.autoneg == AUTONEG_ENABLE) ||
		    (advertising != ADVERTISED_10000baseT_Full) ||
		    (speed + cmd->base.duplex != SPEED_10000 + DUPLEX_FULL))
			return -EINVAL;
	}

	return err;
}