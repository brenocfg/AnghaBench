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
struct mei_cl_device {int /*<<< orphan*/  cl; int /*<<< orphan*/  rx_work; scalar_t__ rx_cb; struct mei_device* bus; } ;
typedef  scalar_t__ mei_cldev_cb_t ;

/* Variables and functions */
 int EALREADY ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cl_bus_rx_work ; 
 int /*<<< orphan*/  mei_cl_mtu (int /*<<< orphan*/ ) ; 
 int mei_cl_read_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mei_cldev_register_rx_cb(struct mei_cl_device *cldev, mei_cldev_cb_t rx_cb)
{
	struct mei_device *bus = cldev->bus;
	int ret;

	if (!rx_cb)
		return -EINVAL;
	if (cldev->rx_cb)
		return -EALREADY;

	cldev->rx_cb = rx_cb;
	INIT_WORK(&cldev->rx_work, mei_cl_bus_rx_work);

	mutex_lock(&bus->device_lock);
	ret = mei_cl_read_start(cldev->cl, mei_cl_mtu(cldev->cl), NULL);
	mutex_unlock(&bus->device_lock);
	if (ret && ret != -EBUSY)
		return ret;

	return 0;
}