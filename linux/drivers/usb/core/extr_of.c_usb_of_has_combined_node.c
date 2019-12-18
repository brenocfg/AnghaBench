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
struct usb_device_descriptor {int bDeviceClass; int bNumConfigurations; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct usb_device {TYPE_2__* config; TYPE_1__ dev; struct usb_device_descriptor descriptor; } ;
struct usb_config_descriptor {int bNumInterfaces; } ;
struct TYPE_4__ {struct usb_config_descriptor desc; } ;

/* Variables and functions */
#define  USB_CLASS_HUB 129 
#define  USB_CLASS_PER_INTERFACE 128 

bool usb_of_has_combined_node(struct usb_device *udev)
{
	struct usb_device_descriptor *ddesc = &udev->descriptor;
	struct usb_config_descriptor *cdesc;

	if (!udev->dev.of_node)
		return false;

	switch (ddesc->bDeviceClass) {
	case USB_CLASS_PER_INTERFACE:
	case USB_CLASS_HUB:
		if (ddesc->bNumConfigurations == 1) {
			cdesc = &udev->config->desc;
			if (cdesc->bNumInterfaces == 1)
				return true;
		}
	}

	return false;
}