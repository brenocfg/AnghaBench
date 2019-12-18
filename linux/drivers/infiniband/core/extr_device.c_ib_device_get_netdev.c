#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ reg_state; } ;
struct ib_port_data {int /*<<< orphan*/  netdev_lock; int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {struct net_device* (* get_netdev ) (struct ib_device*,unsigned int) ;} ;
struct ib_device {TYPE_1__ ops; struct ib_port_data* port_data; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct net_device* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct net_device* stub1 (struct ib_device*,unsigned int) ; 

struct net_device *ib_device_get_netdev(struct ib_device *ib_dev,
					unsigned int port)
{
	struct ib_port_data *pdata;
	struct net_device *res;

	if (!rdma_is_port_valid(ib_dev, port))
		return NULL;

	pdata = &ib_dev->port_data[port];

	/*
	 * New drivers should use ib_device_set_netdev() not the legacy
	 * get_netdev().
	 */
	if (ib_dev->ops.get_netdev)
		res = ib_dev->ops.get_netdev(ib_dev, port);
	else {
		spin_lock(&pdata->netdev_lock);
		res = rcu_dereference_protected(
			pdata->netdev, lockdep_is_held(&pdata->netdev_lock));
		if (res)
			dev_hold(res);
		spin_unlock(&pdata->netdev_lock);
	}

	/*
	 * If we are starting to unregister expedite things by preventing
	 * propagation of an unregistering netdev.
	 */
	if (res && res->reg_state != NETREG_REGISTERED) {
		dev_put(res);
		return NULL;
	}

	return res;
}