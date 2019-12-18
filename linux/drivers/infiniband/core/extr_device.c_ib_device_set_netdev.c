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
struct ib_port_data {int /*<<< orphan*/  netdev_lock; int /*<<< orphan*/  netdev; } ;
struct ib_device {struct ib_port_data* port_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  add_ndev_hash (struct ib_port_data*) ; 
 int alloc_port_data (struct ib_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_device_set_netdev(struct ib_device *ib_dev, struct net_device *ndev,
			 unsigned int port)
{
	struct net_device *old_ndev;
	struct ib_port_data *pdata;
	unsigned long flags;
	int ret;

	/*
	 * Drivers wish to call this before ib_register_driver, so we have to
	 * setup the port data early.
	 */
	ret = alloc_port_data(ib_dev);
	if (ret)
		return ret;

	if (!rdma_is_port_valid(ib_dev, port))
		return -EINVAL;

	pdata = &ib_dev->port_data[port];
	spin_lock_irqsave(&pdata->netdev_lock, flags);
	old_ndev = rcu_dereference_protected(
		pdata->netdev, lockdep_is_held(&pdata->netdev_lock));
	if (old_ndev == ndev) {
		spin_unlock_irqrestore(&pdata->netdev_lock, flags);
		return 0;
	}

	if (ndev)
		dev_hold(ndev);
	rcu_assign_pointer(pdata->netdev, ndev);
	spin_unlock_irqrestore(&pdata->netdev_lock, flags);

	add_ndev_hash(pdata);
	if (old_ndev)
		dev_put(old_ndev);

	return 0;
}