#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roccat_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  hid; scalar_t__ open; TYPE_1__* dev; scalar_t__ exist; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct roccat_device** devices ; 
 int /*<<< orphan*/  devices_lock ; 
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct roccat_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roccat_major ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void roccat_disconnect(int minor)
{
	struct roccat_device *device;

	mutex_lock(&devices_lock);
	device = devices[minor];
	mutex_unlock(&devices_lock);

	device->exist = 0; /* TODO exist maybe not needed */

	device_destroy(device->dev->class, MKDEV(roccat_major, minor));

	mutex_lock(&devices_lock);
	devices[minor] = NULL;
	mutex_unlock(&devices_lock);

	if (device->open) {
		hid_hw_close(device->hid);
		wake_up_interruptible(&device->wait);
	} else {
		kfree(device);
	}
}