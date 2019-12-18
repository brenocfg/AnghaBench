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
struct failover {int /*<<< orphan*/  failover_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  failover_slave_unregister (struct net_device*) ; 
 int /*<<< orphan*/  failover_unregister (struct failover*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

void net_failover_destroy(struct failover *failover)
{
	struct net_failover_info *nfo_info;
	struct net_device *failover_dev;
	struct net_device *slave_dev;

	if (!failover)
		return;

	failover_dev = rcu_dereference(failover->failover_dev);
	nfo_info = netdev_priv(failover_dev);

	netif_device_detach(failover_dev);

	rtnl_lock();

	slave_dev = rtnl_dereference(nfo_info->primary_dev);
	if (slave_dev)
		failover_slave_unregister(slave_dev);

	slave_dev = rtnl_dereference(nfo_info->standby_dev);
	if (slave_dev)
		failover_slave_unregister(slave_dev);

	failover_unregister(failover);

	unregister_netdevice(failover_dev);

	rtnl_unlock();

	free_netdev(failover_dev);
}