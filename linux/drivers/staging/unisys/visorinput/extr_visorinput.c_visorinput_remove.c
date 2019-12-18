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
struct visorinput_devdata {int /*<<< orphan*/  visorinput_dev; int /*<<< orphan*/  lock_visor_dev; } ;
struct visor_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct visorinput_devdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct visorinput_devdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_client_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visorbus_disable_channel_interrupts (struct visor_device*) ; 

__attribute__((used)) static void visorinput_remove(struct visor_device *dev)
{
	struct visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	if (!devdata)
		return;

	mutex_lock(&devdata->lock_visor_dev);
	visorbus_disable_channel_interrupts(dev);

	/*
	 * due to above, at this time no thread of execution will be in
	 * visorinput_channel_interrupt()
	 */

	dev_set_drvdata(&dev->device, NULL);
	mutex_unlock(&devdata->lock_visor_dev);

	unregister_client_input(devdata->visorinput_dev);
	kfree(devdata);
}