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
struct usb_hub {TYPE_1__** ports; } ;
struct usb_hcd {int dev_policy; } ;
struct usb_device {int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  connect_type; } ;

/* Variables and functions */
#define  USB_DEVICE_AUTHORIZE_ALL 130 
#define  USB_DEVICE_AUTHORIZE_INTERNAL 129 
#define  USB_DEVICE_AUTHORIZE_NONE 128 
 int /*<<< orphan*/  USB_PORT_CONNECT_TYPE_HARD_WIRED ; 
 struct usb_hub* usb_hub_to_struct_hub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool usb_dev_authorized(struct usb_device *dev, struct usb_hcd *hcd)
{
	struct usb_hub *hub;

	if (!dev->parent)
		return true; /* Root hub always ok [and always wired] */

	switch (hcd->dev_policy) {
	case USB_DEVICE_AUTHORIZE_NONE:
	default:
		return false;

	case USB_DEVICE_AUTHORIZE_ALL:
		return true;

	case USB_DEVICE_AUTHORIZE_INTERNAL:
		hub = usb_hub_to_struct_hub(dev->parent);
		return hub->ports[dev->portnum - 1]->connect_type ==
				USB_PORT_CONNECT_TYPE_HARD_WIRED;
	}
}