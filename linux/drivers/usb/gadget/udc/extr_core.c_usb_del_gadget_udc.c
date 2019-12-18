#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  parent; } ;
struct usb_udc {TYPE_1__ dev; struct usb_gadget_driver* driver; int /*<<< orphan*/  list; } ;
struct usb_gadget_driver {int /*<<< orphan*/  pending; } ;
struct usb_gadget {TYPE_1__ dev; int /*<<< orphan*/  work; struct usb_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gadget_driver_pending_list ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_lock ; 
 int /*<<< orphan*/  usb_gadget_remove_driver (struct usb_udc*) ; 

void usb_del_gadget_udc(struct usb_gadget *gadget)
{
	struct usb_udc *udc = gadget->udc;

	if (!udc)
		return;

	dev_vdbg(gadget->dev.parent, "unregistering gadget\n");

	mutex_lock(&udc_lock);
	list_del(&udc->list);

	if (udc->driver) {
		struct usb_gadget_driver *driver = udc->driver;

		usb_gadget_remove_driver(udc);
		list_add(&driver->pending, &gadget_driver_pending_list);
	}
	mutex_unlock(&udc_lock);

	kobject_uevent(&udc->dev.kobj, KOBJ_REMOVE);
	flush_work(&gadget->work);
	device_unregister(&udc->dev);
	device_unregister(&gadget->dev);
	memset(&gadget->dev, 0x00, sizeof(gadget->dev));
}