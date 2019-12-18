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
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
struct ipoib_walk_data {struct net_device* result; struct sockaddr const* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 scalar_t__ ipoib_is_dev_match_addr_rcu (struct sockaddr const*,struct net_device*) ; 
 int /*<<< orphan*/  ipoib_upper_walk ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct ipoib_walk_data*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct net_device *ipoib_get_net_dev_match_addr(
		const struct sockaddr *addr, struct net_device *dev)
{
	struct ipoib_walk_data data = {
		.addr = addr,
	};

	rcu_read_lock();
	if (ipoib_is_dev_match_addr_rcu(addr, dev)) {
		dev_hold(dev);
		data.result = dev;
		goto out;
	}

	netdev_walk_all_upper_dev_rcu(dev, ipoib_upper_walk, &data);
out:
	rcu_read_unlock();
	return data.result;
}