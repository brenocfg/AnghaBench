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
struct rio_dev {int pef; TYPE_2__* net; TYPE_1__* rswitch; int /*<<< orphan*/  net_list; int /*<<< orphan*/  global_list; int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  switches; int /*<<< orphan*/  devices; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIO_DEVICE_RUNNING ; 
 int RIO_PEF_SWITCH ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_devices ; 
 int /*<<< orphan*/  rio_global_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int rio_add_device(struct rio_dev *rdev)
{
	int err;

	atomic_set(&rdev->state, RIO_DEVICE_RUNNING);
	err = device_register(&rdev->dev);
	if (err)
		return err;

	spin_lock(&rio_global_list_lock);
	list_add_tail(&rdev->global_list, &rio_devices);
	if (rdev->net) {
		list_add_tail(&rdev->net_list, &rdev->net->devices);
		if (rdev->pef & RIO_PEF_SWITCH)
			list_add_tail(&rdev->rswitch->node,
				      &rdev->net->switches);
	}
	spin_unlock(&rio_global_list_lock);

	return 0;
}