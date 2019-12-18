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
struct TYPE_4__ {int spd_dpx; } ;
struct velocity_info {TYPE_2__ options; int /*<<< orphan*/  mac_regs; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ speed; scalar_t__ duplex; scalar_t__ autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
typedef  enum speed_opt { ____Placeholder_speed_opt } speed_opt ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int SPD_DPX_1000_FULL ; 
 int SPD_DPX_100_FULL ; 
 int SPD_DPX_100_HALF ; 
 int SPD_DPX_10_FULL ; 
 int SPD_DPX_10_HALF ; 
 int SPD_DPX_AUTO ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ VELOCITY_AUTONEG_ENABLE ; 
 scalar_t__ VELOCITY_DUPLEX_FULL ; 
 scalar_t__ VELOCITY_LINK_FAIL ; 
 scalar_t__ VELOCITY_SPEED_10 ; 
 scalar_t__ VELOCITY_SPEED_100 ; 
 scalar_t__ VELOCITY_SPEED_1000 ; 
 scalar_t__ check_connection_type (int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  velocity_set_media_mode (struct velocity_info*,scalar_t__) ; 

__attribute__((used)) static int velocity_set_link_ksettings(struct net_device *dev,
				       const struct ethtool_link_ksettings *cmd)
{
	struct velocity_info *vptr = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u32 curr_status;
	u32 new_status = 0;
	int ret = 0;

	curr_status = check_connection_type(vptr->mac_regs);
	curr_status &= (~VELOCITY_LINK_FAIL);

	new_status |= ((cmd->base.autoneg) ? VELOCITY_AUTONEG_ENABLE : 0);
	new_status |= ((speed == SPEED_1000) ? VELOCITY_SPEED_1000 : 0);
	new_status |= ((speed == SPEED_100) ? VELOCITY_SPEED_100 : 0);
	new_status |= ((speed == SPEED_10) ? VELOCITY_SPEED_10 : 0);
	new_status |= ((cmd->base.duplex == DUPLEX_FULL) ?
		       VELOCITY_DUPLEX_FULL : 0);

	if ((new_status & VELOCITY_AUTONEG_ENABLE) &&
	    (new_status != (curr_status | VELOCITY_AUTONEG_ENABLE))) {
		ret = -EINVAL;
	} else {
		enum speed_opt spd_dpx;

		if (new_status & VELOCITY_AUTONEG_ENABLE)
			spd_dpx = SPD_DPX_AUTO;
		else if ((new_status & VELOCITY_SPEED_1000) &&
			 (new_status & VELOCITY_DUPLEX_FULL)) {
			spd_dpx = SPD_DPX_1000_FULL;
		} else if (new_status & VELOCITY_SPEED_100)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_100_FULL : SPD_DPX_100_HALF;
		else if (new_status & VELOCITY_SPEED_10)
			spd_dpx = (new_status & VELOCITY_DUPLEX_FULL) ?
				SPD_DPX_10_FULL : SPD_DPX_10_HALF;
		else
			return -EOPNOTSUPP;

		vptr->options.spd_dpx = spd_dpx;

		velocity_set_media_mode(vptr, new_status);
	}

	return ret;
}