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
typedef  int u32 ;
struct typhoon {int speed; int duplex; void* xcvr_select; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int speed; scalar_t__ autoneg; int duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct cmd_desc {void* parm1; } ;
typedef  void* __le16 ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_COMMAND_NO_RESPONSE (struct cmd_desc*,int /*<<< orphan*/ ) ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int /*<<< orphan*/  TYPHOON_CMD_XCVR_SELECT ; 
 void* TYPHOON_XCVR_100FULL ; 
 void* TYPHOON_XCVR_100HALF ; 
 void* TYPHOON_XCVR_10FULL ; 
 void* TYPHOON_XCVR_10HALF ; 
 void* TYPHOON_XCVR_AUTONEG ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int typhoon_issue_command (struct typhoon*,int,struct cmd_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
typhoon_set_link_ksettings(struct net_device *dev,
			   const struct ethtool_link_ksettings *cmd)
{
	struct typhoon *tp = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	struct cmd_desc xp_cmd;
	__le16 xcvr;
	int err;

	err = -EINVAL;
	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		xcvr = TYPHOON_XCVR_AUTONEG;
	} else {
		if (cmd->base.duplex == DUPLEX_HALF) {
			if (speed == SPEED_10)
				xcvr = TYPHOON_XCVR_10HALF;
			else if (speed == SPEED_100)
				xcvr = TYPHOON_XCVR_100HALF;
			else
				goto out;
		} else if (cmd->base.duplex == DUPLEX_FULL) {
			if (speed == SPEED_10)
				xcvr = TYPHOON_XCVR_10FULL;
			else if (speed == SPEED_100)
				xcvr = TYPHOON_XCVR_100FULL;
			else
				goto out;
		} else
			goto out;
	}

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_XCVR_SELECT);
	xp_cmd.parm1 = xcvr;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);
	if(err < 0)
		goto out;

	tp->xcvr_select = xcvr;
	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		tp->speed = 0xff;	/* invalid */
		tp->duplex = 0xff;	/* invalid */
	} else {
		tp->speed = speed;
		tp->duplex = cmd->base.duplex;
	}

out:
	return err;
}