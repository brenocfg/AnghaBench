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
struct mei_device {scalar_t__ dev_state; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  device_lock; scalar_t__ reset_count; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MEI_DEV_DISABLED ; 
 int /*<<< orphan*/  MEI_DEV_POWER_UP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mei_reset (struct mei_device*) ; 
 int /*<<< orphan*/  mei_set_devstate (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int mei_restart(struct mei_device *dev)
{
	int err;

	mutex_lock(&dev->device_lock);

	mei_set_devstate(dev, MEI_DEV_POWER_UP);
	dev->reset_count = 0;

	err = mei_reset(dev);

	mutex_unlock(&dev->device_lock);

	if (err == -ENODEV || dev->dev_state == MEI_DEV_DISABLED) {
		dev_err(dev->dev, "device disabled = %d\n", err);
		return -ENODEV;
	}

	/* try to start again */
	if (err)
		schedule_work(&dev->reset_work);


	return 0;
}