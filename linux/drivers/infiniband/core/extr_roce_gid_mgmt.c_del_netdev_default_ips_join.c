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
 int /*<<< orphan*/  bond_delete_netdev_default_gids (struct ib_device*,int /*<<< orphan*/ ,struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void del_netdev_default_ips_join(struct ib_device *ib_dev, u8 port,
					struct net_device *rdma_ndev,
					void *cookie)
{
	struct net_device *master_ndev;

	rcu_read_lock();
	master_ndev = netdev_master_upper_dev_get_rcu(rdma_ndev);
	if (master_ndev)
		dev_hold(master_ndev);
	rcu_read_unlock();

	if (master_ndev) {
		bond_delete_netdev_default_gids(ib_dev, port, rdma_ndev,
						master_ndev);
		dev_put(master_ndev);
	}
}