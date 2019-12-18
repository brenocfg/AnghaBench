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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct net_device *ipoib_get_master_net_dev(struct net_device *dev)
{
	struct net_device *master;

	rcu_read_lock();
	master = netdev_master_upper_dev_get_rcu(dev);
	if (master)
		dev_hold(master);
	rcu_read_unlock();

	if (master)
		return master;

	dev_hold(dev);
	return dev;
}