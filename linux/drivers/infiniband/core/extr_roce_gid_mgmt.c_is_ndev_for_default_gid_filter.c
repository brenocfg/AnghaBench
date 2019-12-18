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
 scalar_t__ netif_is_bond_master (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bond_slave (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rdma_is_upper_dev_rcu (struct net_device*,struct net_device*) ; 

__attribute__((used)) static bool
is_ndev_for_default_gid_filter(struct ib_device *ib_dev, u8 port,
			       struct net_device *rdma_ndev, void *cookie)
{
	struct net_device *cookie_ndev = cookie;
	bool res;

	if (!rdma_ndev)
		return false;

	rcu_read_lock();

	/*
	 * When rdma netdevice is used in bonding, bonding master netdevice
	 * should be considered for default GIDs. Therefore, ignore slave rdma
	 * netdevices when bonding is considered.
	 * Additionally when event(cookie) netdevice is bond master device,
	 * make sure that it the upper netdevice of rdma netdevice.
	 */
	res = ((cookie_ndev == rdma_ndev && !netif_is_bond_slave(rdma_ndev)) ||
	       (netif_is_bond_master(cookie_ndev) &&
		rdma_is_upper_dev_rcu(rdma_ndev, cookie_ndev)));

	rcu_read_unlock();
	return res;
}