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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int REQUIRED_BOND_STATES ; 
 int is_eth_active_slave_of_bonding_rcu (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rdma_is_upper_dev_rcu (struct net_device*,void*) ; 
 struct net_device* rdma_vlan_dev_real_dev (void*) ; 

__attribute__((used)) static bool
is_eth_port_of_netdev_filter(struct ib_device *ib_dev, u8 port,
			     struct net_device *rdma_ndev, void *cookie)
{
	struct net_device *real_dev;
	bool res;

	if (!rdma_ndev)
		return false;

	rcu_read_lock();
	real_dev = rdma_vlan_dev_real_dev(cookie);
	if (!real_dev)
		real_dev = cookie;

	res = ((rdma_is_upper_dev_rcu(rdma_ndev, cookie) &&
	       (is_eth_active_slave_of_bonding_rcu(rdma_ndev, real_dev) &
		REQUIRED_BOND_STATES)) ||
	       real_dev == rdma_ndev);

	rcu_read_unlock();
	return res;
}