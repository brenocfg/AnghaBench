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
struct xhci_hcd {struct xhci_hub usb3_rhub; } ;
struct TYPE_5__ {int /*<<< orphan*/  DeviceRemovable; scalar_t__ wHubDelay; scalar_t__ bHubHdrDecLat; } ;
struct TYPE_6__ {TYPE_2__ ss; } ;
struct usb_hub_descriptor {TYPE_3__ u; int /*<<< orphan*/  bDescLength; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int PORT_DEV_REMOVE ; 
 int /*<<< orphan*/  USB_DT_SS_HUB ; 
 int /*<<< orphan*/  USB_DT_SS_HUB_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_common_hub_descriptor (struct xhci_hcd*,struct usb_hub_descriptor*,int) ; 

__attribute__((used)) static void xhci_usb3_hub_descriptor(struct usb_hcd *hcd, struct xhci_hcd *xhci,
		struct usb_hub_descriptor *desc)
{
	int ports;
	u16 port_removable;
	u32 portsc;
	unsigned int i;
	struct xhci_hub *rhub;

	rhub = &xhci->usb3_rhub;
	ports = rhub->num_ports;
	xhci_common_hub_descriptor(xhci, desc, ports);
	desc->bDescriptorType = USB_DT_SS_HUB;
	desc->bDescLength = USB_DT_SS_HUB_SIZE;

	/* header decode latency should be zero for roothubs,
	 * see section 4.23.5.2.
	 */
	desc->u.ss.bHubHdrDecLat = 0;
	desc->u.ss.wHubDelay = 0;

	port_removable = 0;
	/* bit 0 is reserved, bit 1 is for port 1, etc. */
	for (i = 0; i < ports; i++) {
		portsc = readl(rhub->ports[i]->addr);
		if (portsc & PORT_DEV_REMOVE)
			port_removable |= 1 << (i + 1);
	}

	desc->u.ss.DeviceRemovable = cpu_to_le16(port_removable);
}