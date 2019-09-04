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
struct usbhid_device {int /*<<< orphan*/  intf; } ;
struct hiddev {int /*<<< orphan*/  existancelock; int /*<<< orphan*/  wait; int /*<<< orphan*/  hid; scalar_t__ open; scalar_t__ exist; } ;
struct hid_device {struct usbhid_device* driver_data; struct hiddev* hiddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_hw_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hiddev_class ; 
 int /*<<< orphan*/  kfree (struct hiddev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hiddev_disconnect(struct hid_device *hid)
{
	struct hiddev *hiddev = hid->hiddev;
	struct usbhid_device *usbhid = hid->driver_data;

	usb_deregister_dev(usbhid->intf, &hiddev_class);

	mutex_lock(&hiddev->existancelock);
	hiddev->exist = 0;

	if (hiddev->open) {
		mutex_unlock(&hiddev->existancelock);
		hid_hw_close(hiddev->hid);
		wake_up_interruptible(&hiddev->wait);
	} else {
		mutex_unlock(&hiddev->existancelock);
		kfree(hiddev);
	}
}