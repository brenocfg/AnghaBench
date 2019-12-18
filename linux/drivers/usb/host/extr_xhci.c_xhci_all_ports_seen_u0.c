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
struct TYPE_2__ {int num_ports; } ;
struct xhci_hcd {int port_status_u0; TYPE_1__ usb3_rhub; } ;

/* Variables and functions */

__attribute__((used)) static int xhci_all_ports_seen_u0(struct xhci_hcd *xhci)
{
	return (xhci->port_status_u0 == ((1 << xhci->usb3_rhub.num_ports) - 1));
}