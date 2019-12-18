#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {scalar_t__ product; scalar_t__ manufacturer; TYPE_1__* actconfig; } ;
struct TYPE_4__ {int bmAttributes; } ;
struct TYPE_3__ {TYPE_2__ desc; } ;

/* Variables and functions */
 char const* RC_MAP_MEDION_X10 ; 
 char const* RC_MAP_MEDION_X10_DIGITAINER ; 
 char const* RC_MAP_MEDION_X10_OR2X ; 
 int USB_CONFIG_ATT_WAKEUP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static const char *get_medion_keymap(struct usb_interface *interface)
{
	struct usb_device *udev = interface_to_usbdev(interface);

	/*
	 * There are many different Medion remotes shipped with a receiver
	 * with the same usb id, but the receivers have subtle differences
	 * in the USB descriptors allowing us to detect them.
	 */

	if (udev->manufacturer && udev->product) {
		if (udev->actconfig->desc.bmAttributes & USB_CONFIG_ATT_WAKEUP) {

			if (!strcmp(udev->manufacturer, "X10 Wireless Technology Inc")
			    && !strcmp(udev->product, "USB Receiver"))
				return RC_MAP_MEDION_X10_DIGITAINER;

			if (!strcmp(udev->manufacturer, "X10 WTI")
			    && !strcmp(udev->product, "RF receiver"))
				return RC_MAP_MEDION_X10_OR2X;
		} else {

			 if (!strcmp(udev->manufacturer, "X10 Wireless Technology Inc")
			    && !strcmp(udev->product, "USB Receiver"))
				return RC_MAP_MEDION_X10;
		}
	}

	dev_info(&interface->dev,
		 "Unknown Medion X10 receiver, using default ati_remote Medion keymap\n");

	return RC_MAP_MEDION_X10;
}