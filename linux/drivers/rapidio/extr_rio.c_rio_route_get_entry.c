#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_switch_ops {int (* get_entry ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  owner; } ;
struct rio_dev {int /*<<< orphan*/  hopcount; int /*<<< orphan*/  destid; TYPE_2__* net; TYPE_1__* rswitch; } ;
struct TYPE_4__ {int /*<<< orphan*/  hport; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct rio_switch_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int rio_lock_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rio_std_route_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_unlock_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

int rio_route_get_entry(struct rio_dev *rdev, u16 table,
			u16 route_destid, u8 *route_port, int lock)
{
	int rc = -EINVAL;
	struct rio_switch_ops *ops = rdev->rswitch->ops;

	if (lock) {
		rc = rio_lock_device(rdev->net->hport, rdev->destid,
				     rdev->hopcount, 1000);
		if (rc)
			return rc;
	}

	spin_lock(&rdev->rswitch->lock);

	if (!ops || !ops->get_entry) {
		rc = rio_std_route_get_entry(rdev->net->hport, rdev->destid,
					     rdev->hopcount, table,
					     route_destid, route_port);
	} else if (try_module_get(ops->owner)) {
		rc = ops->get_entry(rdev->net->hport, rdev->destid,
				    rdev->hopcount, table, route_destid,
				    route_port);
		module_put(ops->owner);
	}

	spin_unlock(&rdev->rswitch->lock);

	if (lock)
		rio_unlock_device(rdev->net->hport, rdev->destid,
				  rdev->hopcount);
	return rc;
}