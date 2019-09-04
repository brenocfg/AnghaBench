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
struct mei_device {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  dev; } ;
struct mei_cl_device {struct mei_device* bus; struct mei_cl* cl; } ;
struct mei_cl {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mei_cl_disconnect (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_flush_queues (struct mei_cl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_unlink (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cldev_unregister_callbacks (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mei_cldev_disable(struct mei_cl_device *cldev)
{
	struct mei_device *bus;
	struct mei_cl *cl;
	int err;

	if (!cldev)
		return -ENODEV;

	cl = cldev->cl;

	bus = cldev->bus;

	mei_cldev_unregister_callbacks(cldev);

	mutex_lock(&bus->device_lock);

	if (!mei_cl_is_connected(cl)) {
		dev_dbg(bus->dev, "Already disconnected\n");
		err = 0;
		goto out;
	}

	err = mei_cl_disconnect(cl);
	if (err < 0)
		dev_err(bus->dev, "Could not disconnect from the ME client\n");

out:
	/* Flush queues and remove any pending read */
	mei_cl_flush_queues(cl, NULL);
	mei_cl_unlink(cl);

	mutex_unlock(&bus->device_lock);
	return err;
}