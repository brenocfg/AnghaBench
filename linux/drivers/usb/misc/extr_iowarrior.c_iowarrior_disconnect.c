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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct iowarrior {int minor; int /*<<< orphan*/  mutex; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  submitted; int /*<<< orphan*/  int_in_urb; scalar_t__ opened; scalar_t__ present; } ;

/* Variables and functions */
 scalar_t__ IOWARRIOR_MINOR_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iowarrior_class ; 
 int /*<<< orphan*/  iowarrior_delete (struct iowarrior*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct iowarrior* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iowarrior_disconnect(struct usb_interface *interface)
{
	struct iowarrior *dev = usb_get_intfdata(interface);
	int minor = dev->minor;

	usb_deregister_dev(interface, &iowarrior_class);

	mutex_lock(&dev->mutex);

	/* prevent device read, write and ioctl */
	dev->present = 0;

	if (dev->opened) {
		/* There is a process that holds a filedescriptor to the device ,
		   so we only shutdown read-/write-ops going on.
		   Deleting the device is postponed until close() was called.
		 */
		usb_kill_urb(dev->int_in_urb);
		usb_kill_anchored_urbs(&dev->submitted);
		wake_up_interruptible(&dev->read_wait);
		wake_up_interruptible(&dev->write_wait);
		mutex_unlock(&dev->mutex);
	} else {
		/* no process is using the device, cleanup now */
		mutex_unlock(&dev->mutex);
		iowarrior_delete(dev);
	}

	dev_info(&interface->dev, "I/O-Warror #%d now disconnected\n",
		 minor - IOWARRIOR_MINOR_BASE);
}