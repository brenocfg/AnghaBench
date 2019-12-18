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
struct usbnet {int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct cdc_state {struct usb_interface* control; struct usb_interface* data; } ;

/* Variables and functions */
 struct usb_driver* driver_of (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void usbnet_cdc_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct cdc_state		*info = (void *) &dev->data;
	struct usb_driver		*driver = driver_of(intf);

	/* combined interface - nothing  to do */
	if (info->data == info->control)
		return;

	/* disconnect master --> disconnect slave */
	if (intf == info->control && info->data) {
		/* ensure immediate exit from usbnet_disconnect */
		usb_set_intfdata(info->data, NULL);
		usb_driver_release_interface(driver, info->data);
		info->data = NULL;
	}

	/* and vice versa (just in case) */
	else if (intf == info->data && info->control) {
		/* ensure immediate exit from usbnet_disconnect */
		usb_set_intfdata(info->control, NULL);
		usb_driver_release_interface(driver, info->control);
		info->control = NULL;
	}
}