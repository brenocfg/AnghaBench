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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ bDeviceClass; int /*<<< orphan*/  iProduct; } ;
struct usb_device {TYPE_1__ descriptor; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int /*<<< orphan*/  cxacru_driver ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ usb_string (struct usb_device*,int /*<<< orphan*/ ,char*,int) ; 
 int usbatm_usb_probe (struct usb_interface*,struct usb_device_id const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxacru_usb_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	char buf[15];

	/* Avoid ADSL routers (cx82310_eth).
	 * Abort if bDeviceClass is 0xff and iProduct is "USB NET CARD".
	 */
	if (usb_dev->descriptor.bDeviceClass == USB_CLASS_VENDOR_SPEC
			&& usb_string(usb_dev, usb_dev->descriptor.iProduct,
				buf, sizeof(buf)) > 0) {
		if (!strcmp(buf, "USB NET CARD")) {
			dev_info(&intf->dev, "ignoring cx82310_eth device\n");
			return -ENODEV;
		}
	}

	return usbatm_usb_probe(intf, id, &cxacru_driver);
}