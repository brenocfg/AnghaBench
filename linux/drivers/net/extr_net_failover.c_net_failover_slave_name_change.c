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
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_failover_slave_name_change(struct net_device *slave_dev,
					  struct net_device *failover_dev)
{
	struct net_device *primary_dev, *standby_dev;
	struct net_failover_info *nfo_info;

	nfo_info = netdev_priv(failover_dev);

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	if (slave_dev != primary_dev && slave_dev != standby_dev)
		return -ENODEV;

	/* We need to bring up the slave after the rename by udev in case
	 * open failed with EBUSY when it was registered.
	 */
	dev_open(slave_dev, NULL);

	return 0;
}