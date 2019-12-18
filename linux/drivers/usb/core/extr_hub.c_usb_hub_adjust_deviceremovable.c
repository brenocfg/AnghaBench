#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct usb_port {int connect_type; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  DeviceRemovable; } ;
struct TYPE_4__ {int* DeviceRemovable; } ;
struct TYPE_6__ {TYPE_2__ ss; TYPE_1__ hs; } ;
struct usb_hub_descriptor {TYPE_3__ u; } ;
struct usb_hub {struct usb_port** ports; } ;
struct usb_device {int maxchild; } ;
typedef  enum usb_port_connect_type { ____Placeholder_usb_port_connect_type } usb_port_connect_type ;

/* Variables and functions */
 int USB_PORT_CONNECT_TYPE_HARD_WIRED ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hub_is_superspeed (struct usb_device*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct usb_hub* usb_hub_to_struct_hub (struct usb_device*) ; 

void usb_hub_adjust_deviceremovable(struct usb_device *hdev,
		struct usb_hub_descriptor *desc)
{
	struct usb_hub *hub = usb_hub_to_struct_hub(hdev);
	enum usb_port_connect_type connect_type;
	int i;

	if (!hub)
		return;

	if (!hub_is_superspeed(hdev)) {
		for (i = 1; i <= hdev->maxchild; i++) {
			struct usb_port *port_dev = hub->ports[i - 1];

			connect_type = port_dev->connect_type;
			if (connect_type == USB_PORT_CONNECT_TYPE_HARD_WIRED) {
				u8 mask = 1 << (i%8);

				if (!(desc->u.hs.DeviceRemovable[i/8] & mask)) {
					dev_dbg(&port_dev->dev, "DeviceRemovable is changed to 1 according to platform information.\n");
					desc->u.hs.DeviceRemovable[i/8]	|= mask;
				}
			}
		}
	} else {
		u16 port_removable = le16_to_cpu(desc->u.ss.DeviceRemovable);

		for (i = 1; i <= hdev->maxchild; i++) {
			struct usb_port *port_dev = hub->ports[i - 1];

			connect_type = port_dev->connect_type;
			if (connect_type == USB_PORT_CONNECT_TYPE_HARD_WIRED) {
				u16 mask = 1 << i;

				if (!(port_removable & mask)) {
					dev_dbg(&port_dev->dev, "DeviceRemovable is changed to 1 according to platform information.\n");
					port_removable |= mask;
				}
			}
		}

		desc->u.ss.DeviceRemovable = cpu_to_le16(port_removable);
	}
}