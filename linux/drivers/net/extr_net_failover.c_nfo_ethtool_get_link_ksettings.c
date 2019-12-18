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
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int __ethtool_get_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  net_failover_xmit_ready (struct net_device*) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfo_ethtool_get_link_ksettings(struct net_device *dev,
					  struct ethtool_link_ksettings *cmd)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *slave_dev;

	slave_dev = rtnl_dereference(nfo_info->primary_dev);
	if (!slave_dev || !net_failover_xmit_ready(slave_dev)) {
		slave_dev = rtnl_dereference(nfo_info->standby_dev);
		if (!slave_dev || !net_failover_xmit_ready(slave_dev)) {
			cmd->base.duplex = DUPLEX_UNKNOWN;
			cmd->base.port = PORT_OTHER;
			cmd->base.speed = SPEED_UNKNOWN;

			return 0;
		}
	}

	return __ethtool_get_link_ksettings(slave_dev, cmd);
}