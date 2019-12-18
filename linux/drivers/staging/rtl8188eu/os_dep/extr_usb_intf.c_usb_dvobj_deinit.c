#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct dvobj_priv {int NumInterfaces; int InterfaceNumber; int /*<<< orphan*/  usb_vendor_req_mutex; } ;
struct TYPE_4__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 TYPE_1__* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct dvobj_priv*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct dvobj_priv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_dvobj_deinit(struct usb_interface *usb_intf)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(usb_intf);

	usb_set_intfdata(usb_intf, NULL);
	if (dvobj) {
		/* Modify condition for 92DU DMDP 2010.11.18, by Thomas */
		if ((dvobj->NumInterfaces != 2 &&
		    dvobj->NumInterfaces != 3) ||
		    (dvobj->InterfaceNumber == 1)) {
			if (interface_to_usbdev(usb_intf)->state !=
			    USB_STATE_NOTATTACHED) {
				/* If we didn't unplug usb dongle and
				 * remove/insert module, driver fails
				 * on sitesurvey for the first time when
				 * device is up . Reset usb port for sitesurvey
				 * fail issue. */
				pr_debug("usb attached..., try to reset usb device\n");
				usb_reset_device(interface_to_usbdev(usb_intf));
			}
		}

		mutex_destroy(&dvobj->usb_vendor_req_mutex);
		kfree(dvobj);
	}

	usb_put_dev(interface_to_usbdev(usb_intf));
}