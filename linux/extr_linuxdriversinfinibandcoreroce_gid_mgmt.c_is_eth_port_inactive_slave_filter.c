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
 scalar_t__ BONDING_SLAVE_STATE_INACTIVE ; 
 scalar_t__ is_eth_active_slave_of_bonding_rcu (struct net_device*,struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool
is_eth_port_inactive_slave_filter(struct ib_device *ib_dev, u8 port,
				  struct net_device *rdma_ndev, void *cookie)
{
	struct net_device *master_dev;
	bool res;

	if (!rdma_ndev)
		return false;

	rcu_read_lock();
	master_dev = netdev_master_upper_dev_get_rcu(rdma_ndev);
	res = is_eth_active_slave_of_bonding_rcu(rdma_ndev, master_dev) ==
		BONDING_SLAVE_STATE_INACTIVE;
	rcu_read_unlock();

	return res;
}