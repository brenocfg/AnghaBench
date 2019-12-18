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
typedef  int /*<<< orphan*/  (* visorbus_state_complete_func ) (struct visor_device*,int /*<<< orphan*/ ) ;
struct visorinput_devdata {int paused; int /*<<< orphan*/  lock_visor_dev; scalar_t__ interrupts_enabled; } ;
struct visor_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct visorinput_devdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visorbus_disable_channel_interrupts (struct visor_device*) ; 

__attribute__((used)) static int visorinput_pause(struct visor_device *dev,
			    visorbus_state_complete_func complete_func)
{
	int rc;
	struct visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	if (!devdata) {
		rc = -ENODEV;
		goto out;
	}

	mutex_lock(&devdata->lock_visor_dev);
	if (devdata->paused) {
		rc = -EBUSY;
		goto out_locked;
	}
	if (devdata->interrupts_enabled)
		visorbus_disable_channel_interrupts(dev);

	/*
	 * due to above, at this time no thread of execution will be in
	 * visorinput_channel_interrupt()
	 */
	devdata->paused = true;
	complete_func(dev, 0);
	rc = 0;
out_locked:
	mutex_unlock(&devdata->lock_visor_dev);
out:
	return rc;
}