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
typedef  int u32 ;
typedef  int u16 ;
struct xhci_hub {int num_ports; TYPE_1__** ports; } ;
struct xhci_hcd {struct xhci_hub usb2_rhub; } ;
struct TYPE_5__ {int* DeviceRemovable; int* PortPwrCtrlMask; } ;
struct TYPE_6__ {TYPE_2__ hs; } ;
struct usb_hub_descriptor {TYPE_3__ u; scalar_t__ bDescLength; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  port_removable ;
typedef  int __u8 ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int PORT_DEV_REMOVE ; 
 int /*<<< orphan*/  USB_DT_HUB ; 
 scalar_t__ USB_DT_HUB_NONVAR_SIZE ; 
 int /*<<< orphan*/  USB_MAXCHILDREN ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_common_hub_descriptor (struct xhci_hcd*,struct usb_hub_descriptor*,int) ; 

__attribute__((used)) static void xhci_usb2_hub_descriptor(struct usb_hcd *hcd, struct xhci_hcd *xhci,
		struct usb_hub_descriptor *desc)
{
	int ports;
	u16 temp;
	__u8 port_removable[(USB_MAXCHILDREN + 1 + 7) / 8];
	u32 portsc;
	unsigned int i;
	struct xhci_hub *rhub;

	rhub = &xhci->usb2_rhub;
	ports = rhub->num_ports;
	xhci_common_hub_descriptor(xhci, desc, ports);
	desc->bDescriptorType = USB_DT_HUB;
	temp = 1 + (ports / 8);
	desc->bDescLength = USB_DT_HUB_NONVAR_SIZE + 2 * temp;

	/* The Device Removable bits are reported on a byte granularity.
	 * If the port doesn't exist within that byte, the bit is set to 0.
	 */
	memset(port_removable, 0, sizeof(port_removable));
	for (i = 0; i < ports; i++) {
		portsc = readl(rhub->ports[i]->addr);
		/* If a device is removable, PORTSC reports a 0, same as in the
		 * hub descriptor DeviceRemovable bits.
		 */
		if (portsc & PORT_DEV_REMOVE)
			/* This math is hairy because bit 0 of DeviceRemovable
			 * is reserved, and bit 1 is for port 1, etc.
			 */
			port_removable[(i + 1) / 8] |= 1 << ((i + 1) % 8);
	}

	/* ch11.h defines a hub descriptor that has room for USB_MAXCHILDREN
	 * ports on it.  The USB 2.0 specification says that there are two
	 * variable length fields at the end of the hub descriptor:
	 * DeviceRemovable and PortPwrCtrlMask.  But since we can have less than
	 * USB_MAXCHILDREN ports, we may need to use the DeviceRemovable array
	 * to set PortPwrCtrlMask bits.  PortPwrCtrlMask must always be set to
	 * 0xFF, so we initialize the both arrays (DeviceRemovable and
	 * PortPwrCtrlMask) to 0xFF.  Then we set the DeviceRemovable for each
	 * set of ports that actually exist.
	 */
	memset(desc->u.hs.DeviceRemovable, 0xff,
			sizeof(desc->u.hs.DeviceRemovable));
	memset(desc->u.hs.PortPwrCtrlMask, 0xff,
			sizeof(desc->u.hs.PortPwrCtrlMask));

	for (i = 0; i < (ports + 1 + 7) / 8; i++)
		memset(&desc->u.hs.DeviceRemovable[i], port_removable[i],
				sizeof(__u8));
}