#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int dev_set_mtu (struct net_device*,int) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_failover_change_mtu(struct net_device *dev, int new_mtu)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *primary_dev, *standby_dev;
	int ret = 0;

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	if (primary_dev) {
		ret = dev_set_mtu(primary_dev, new_mtu);
		if (ret)
			return ret;
	}

	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	if (standby_dev) {
		ret = dev_set_mtu(standby_dev, new_mtu);
		if (ret) {
			if (primary_dev)
				dev_set_mtu(primary_dev, dev->mtu);
			return ret;
		}
	}

	dev->mtu = new_mtu;

	return 0;
}