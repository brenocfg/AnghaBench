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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ autoneg; int speed; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct ehea_port {int full_duplex; int /*<<< orphan*/  port_speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  EHEA_SPEED_AUTONEG ; 
 int EINVAL ; 
 int /*<<< orphan*/  H_SPEED_100M_F ; 
 int /*<<< orphan*/  H_SPEED_100M_H ; 
 int /*<<< orphan*/  H_SPEED_10G_F ; 
 int /*<<< orphan*/  H_SPEED_10M_F ; 
 int /*<<< orphan*/  H_SPEED_10M_H ; 
 int /*<<< orphan*/  H_SPEED_1G_F ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int ehea_set_portspeed (struct ehea_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,char*) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ehea_set_link_ksettings(struct net_device *dev,
				   const struct ethtool_link_ksettings *cmd)
{
	struct ehea_port *port = netdev_priv(dev);
	int ret = 0;
	u32 sp;

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		sp = EHEA_SPEED_AUTONEG;
		goto doit;
	}

	switch (cmd->base.speed) {
	case SPEED_10:
		if (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_10M_F;
		else
			sp = H_SPEED_10M_H;
		break;

	case SPEED_100:
		if (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_100M_F;
		else
			sp = H_SPEED_100M_H;
		break;

	case SPEED_1000:
		if (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_1G_F;
		else
			ret = -EINVAL;
		break;

	case SPEED_10000:
		if (cmd->base.duplex == DUPLEX_FULL)
			sp = H_SPEED_10G_F;
		else
			ret = -EINVAL;
		break;

	default:
			ret = -EINVAL;
		break;
	}

	if (ret)
		goto out;
doit:
	ret = ehea_set_portspeed(port, sp);

	if (!ret)
		netdev_info(dev,
			    "Port speed successfully set: %dMbps %s Duplex\n",
			    port->port_speed,
			    port->full_duplex == 1 ? "Full" : "Half");
out:
	return ret;
}