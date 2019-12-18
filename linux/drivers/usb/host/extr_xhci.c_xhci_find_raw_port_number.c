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
struct xhci_hub {TYPE_1__** ports; } ;
struct usb_hcd {int dummy; } ;
struct TYPE_2__ {int hw_portnum; } ;

/* Variables and functions */
 struct xhci_hub* xhci_get_rhub (struct usb_hcd*) ; 

int xhci_find_raw_port_number(struct usb_hcd *hcd, int port1)
{
	struct xhci_hub *rhub;

	rhub = xhci_get_rhub(hcd);
	return rhub->ports[port1 - 1]->hw_portnum + 1;
}