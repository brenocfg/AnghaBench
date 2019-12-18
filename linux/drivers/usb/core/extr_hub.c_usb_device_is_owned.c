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
struct usb_device {scalar_t__ state; int portnum; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_owner; } ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 struct usb_hub* usb_hub_to_struct_hub (int /*<<< orphan*/ ) ; 

bool usb_device_is_owned(struct usb_device *udev)
{
	struct usb_hub *hub;

	if (udev->state == USB_STATE_NOTATTACHED || !udev->parent)
		return false;
	hub = usb_hub_to_struct_hub(udev->parent);
	return !!hub->ports[udev->portnum - 1]->port_owner;
}