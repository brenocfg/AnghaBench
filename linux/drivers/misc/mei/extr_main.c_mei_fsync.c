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
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  device_lock; } ;
struct mei_cl {scalar_t__ writing_state; int /*<<< orphan*/  tx_wait; struct mei_device* dev; } ;
struct file {struct mei_cl* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 scalar_t__ MEI_DEV_ENABLED ; 
 scalar_t__ MEI_WRITE_COMPLETE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mei_cl_is_connected (struct mei_cl*) ; 
 scalar_t__ mei_cl_is_write_queued (struct mei_cl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mei_fsync(struct file *fp, loff_t start, loff_t end, int datasync)
{
	struct mei_cl *cl = fp->private_data;
	struct mei_device *dev;
	int rets;

	if (WARN_ON(!cl || !cl->dev))
		return -ENODEV;

	dev = cl->dev;

	mutex_lock(&dev->device_lock);

	if (dev->dev_state != MEI_DEV_ENABLED || !mei_cl_is_connected(cl)) {
		rets = -ENODEV;
		goto out;
	}

	while (mei_cl_is_write_queued(cl)) {
		mutex_unlock(&dev->device_lock);
		rets = wait_event_interruptible(cl->tx_wait,
				cl->writing_state == MEI_WRITE_COMPLETE ||
				!mei_cl_is_connected(cl));
		mutex_lock(&dev->device_lock);
		if (rets) {
			if (signal_pending(current))
				rets = -EINTR;
			goto out;
		}
		if (!mei_cl_is_connected(cl)) {
			rets = -ENODEV;
			goto out;
		}
	}
	rets = 0;
out:
	mutex_unlock(&dev->device_lock);
	return rets;
}