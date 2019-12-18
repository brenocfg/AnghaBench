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
 int /*<<< orphan*/  IB_CACHE_GID_DEFAULT_MODE_DELETE ; 
 int /*<<< orphan*/  ib_cache_gid_set_default_gid (struct ib_device*,int /*<<< orphan*/ ,struct net_device*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_eth_active_slave_of_bonding_rcu (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rdma_is_upper_dev_rcu (struct net_device*,struct net_device*) ; 
 struct net_device* rdma_vlan_dev_real_dev (struct net_device*) ; 
 unsigned long roce_gid_type_mask_support (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bond_delete_netdev_default_gids(struct ib_device *ib_dev,
					    u8 port,
					    struct net_device *rdma_ndev,
					    struct net_device *event_ndev)
{
	struct net_device *real_dev = rdma_vlan_dev_real_dev(event_ndev);
	unsigned long gid_type_mask;

	if (!rdma_ndev)
		return;

	if (!real_dev)
		real_dev = event_ndev;

	rcu_read_lock();

	if (((rdma_ndev != event_ndev &&
	      !rdma_is_upper_dev_rcu(rdma_ndev, event_ndev)) ||
	     is_eth_active_slave_of_bonding_rcu(rdma_ndev, real_dev)
						 ==
	     BONDING_SLAVE_STATE_INACTIVE)) {
		rcu_read_unlock();
		return;
	}

	rcu_read_unlock();

	gid_type_mask = roce_gid_type_mask_support(ib_dev, port);

	ib_cache_gid_set_default_gid(ib_dev, port, rdma_ndev,
				     gid_type_mask,
				     IB_CACHE_GID_DEFAULT_MODE_DELETE);
}