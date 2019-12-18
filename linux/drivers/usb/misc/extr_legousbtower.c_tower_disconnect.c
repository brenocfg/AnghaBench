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
struct lego_usb_tower {int minor; int disconnected; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  open_count; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; } ;

/* Variables and functions */
 scalar_t__ LEGO_USB_TOWER_MINOR_BASE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tower_class ; 
 int /*<<< orphan*/  tower_delete (struct lego_usb_tower*) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct lego_usb_tower* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_poison_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tower_disconnect (struct usb_interface *interface)
{
	struct lego_usb_tower *dev;
	int minor;

	dev = usb_get_intfdata (interface);

	minor = dev->minor;

	/* give back our minor and prevent further open() */
	usb_deregister_dev (interface, &tower_class);

	/* stop I/O */
	usb_poison_urb(dev->interrupt_in_urb);
	usb_poison_urb(dev->interrupt_out_urb);

	mutex_lock(&dev->lock);

	/* if the device is not opened, then we clean up right now */
	if (!dev->open_count) {
		mutex_unlock(&dev->lock);
		tower_delete (dev);
	} else {
		dev->disconnected = 1;
		/* wake up pollers */
		wake_up_interruptible_all(&dev->read_wait);
		wake_up_interruptible_all(&dev->write_wait);
		mutex_unlock(&dev->lock);
	}

	dev_info(&interface->dev, "LEGO USB Tower #%d now disconnected\n",
		 (minor - LEGO_USB_TOWER_MINOR_BASE));
}