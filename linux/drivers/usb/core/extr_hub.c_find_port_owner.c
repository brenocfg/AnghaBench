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
struct usb_device {scalar_t__ state; unsigned int maxchild; } ;
struct usb_dev_state {int dummy; } ;
struct TYPE_2__ {struct usb_dev_state* port_owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

__attribute__((used)) static int find_port_owner(struct usb_device *hdev, unsigned port1,
		struct usb_dev_state ***ppowner)
{
	struct usb_hub *hub = usb_hub_to_struct_hub(hdev);

	if (hdev->state == USB_STATE_NOTATTACHED)
		return -ENODEV;
	if (port1 == 0 || port1 > hdev->maxchild)
		return -EINVAL;

	/* Devices not managed by the hub driver
	 * will always have maxchild equal to 0.
	 */
	*ppowner = &(hub->ports[port1 - 1]->port_owner);
	return 0;
}