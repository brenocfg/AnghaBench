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
struct mei_device {int /*<<< orphan*/  device_lock; } ;
struct mei_cl_device {int /*<<< orphan*/  cl; int /*<<< orphan*/  notif_work; scalar_t__ notif_cb; struct mei_device* bus; } ;
typedef  scalar_t__ mei_cldev_cb_t ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cl_bus_notif_work ; 
 int mei_cl_notify_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mei_cldev_register_notif_cb(struct mei_cl_device *cldev,
				mei_cldev_cb_t notif_cb)
{
	struct mei_device *bus = cldev->bus;
	int ret;

	if (!notif_cb)
		return -EINVAL;

	if (cldev->notif_cb)
		return -EALREADY;

	cldev->notif_cb = notif_cb;
	INIT_WORK(&cldev->notif_work, mei_cl_bus_notif_work);

	mutex_lock(&bus->device_lock);
	ret = mei_cl_notify_request(cldev->cl, NULL, 1);
	mutex_unlock(&bus->device_lock);
	if (ret)
		return ret;

	return 0;
}