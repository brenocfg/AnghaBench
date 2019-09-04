#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_3__ base; TYPE_1__ link_modes; } ;
struct TYPE_5__ {int /*<<< orphan*/  line_speed; int /*<<< orphan*/  link_report_flags; } ;
struct bnx2x {scalar_t__ state; TYPE_2__ vf_link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  BNX2X_LINK_REPORT_FD ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_get_vf_link_ksettings(struct net_device *dev,
				       struct ethtool_link_ksettings *cmd)
{
	struct bnx2x *bp = netdev_priv(dev);
	u32 supported, advertising;

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if (bp->state == BNX2X_STATE_OPEN) {
		if (test_bit(BNX2X_LINK_REPORT_FD,
			     &bp->vf_link_vars.link_report_flags))
			cmd->base.duplex = DUPLEX_FULL;
		else
			cmd->base.duplex = DUPLEX_HALF;

		cmd->base.speed = bp->vf_link_vars.line_speed;
	} else {
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
	}

	cmd->base.port		= PORT_OTHER;
	cmd->base.phy_address	= 0;
	cmd->base.autoneg	= AUTONEG_DISABLE;

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d\n"
	   "  autoneg %d\n",
	   cmd->base.cmd, supported, advertising,
	   cmd->base.speed,
	   cmd->base.duplex, cmd->base.port, cmd->base.phy_address,
	   cmd->base.autoneg);

	return 0;
}