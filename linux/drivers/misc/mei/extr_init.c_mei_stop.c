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

/* Variables and functions */
 int /*<<< orphan*/  MEI_DEV_DISABLED ; 
 int /*<<< orphan*/  MEI_DEV_POWER_DOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_cancel_work (struct mei_device*) ; 
 int /*<<< orphan*/  mei_cl_bus_remove_devices (struct mei_device*) ; 
 int /*<<< orphan*/  mei_clear_interrupts (struct mei_device*) ; 
 int /*<<< orphan*/  mei_reset (struct mei_device*) ; 
 int /*<<< orphan*/  mei_set_devstate (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_synchronize_irq (struct mei_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mei_stop(struct mei_device *dev)
{
	dev_dbg(dev->dev, "stopping the device.\n");

	mutex_lock(&dev->device_lock);
	mei_set_devstate(dev, MEI_DEV_POWER_DOWN);
	mutex_unlock(&dev->device_lock);
	mei_cl_bus_remove_devices(dev);

	mei_cancel_work(dev);

	mei_clear_interrupts(dev);
	mei_synchronize_irq(dev);

	mutex_lock(&dev->device_lock);

	mei_reset(dev);
	/* move device to disabled state unconditionally */
	mei_set_devstate(dev, MEI_DEV_DISABLED);

	mutex_unlock(&dev->device_lock);
}