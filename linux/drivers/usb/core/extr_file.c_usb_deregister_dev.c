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
struct usb_interface {int minor; int /*<<< orphan*/ * usb_dev; int /*<<< orphan*/  dev; } ;
struct usb_class_driver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_MAJOR ; 
 int /*<<< orphan*/  destroy_usb_class () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minor_rwsem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* usb_class ; 
 int /*<<< orphan*/ ** usb_minors ; 

void usb_deregister_dev(struct usb_interface *intf,
			struct usb_class_driver *class_driver)
{
	if (intf->minor == -1)
		return;

	dev_dbg(&intf->dev, "removing %d minor\n", intf->minor);
	device_destroy(usb_class->class, MKDEV(USB_MAJOR, intf->minor));

	down_write(&minor_rwsem);
	usb_minors[intf->minor] = NULL;
	up_write(&minor_rwsem);

	intf->usb_dev = NULL;
	intf->minor = -1;
	destroy_usb_class();
}