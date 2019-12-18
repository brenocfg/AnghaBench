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
struct xhci_port {scalar_t__ hcd_portnum; TYPE_2__* rhub; int /*<<< orphan*/  addr; } ;
struct xhci_hcd {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  busnum; } ;
struct TYPE_6__ {TYPE_1__ self; } ;
struct TYPE_5__ {TYPE_3__* hcd; } ;

/* Variables and functions */
 int PORT_LINK_STROBE ; 
 int PORT_PLS_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int xhci_port_state_to_neutral (int) ; 

void xhci_set_link_state(struct xhci_hcd *xhci, struct xhci_port *port,
			 u32 link_state)
{
	u32 temp;
	u32 portsc;

	portsc = readl(port->addr);
	temp = xhci_port_state_to_neutral(portsc);
	temp &= ~PORT_PLS_MASK;
	temp |= PORT_LINK_STROBE | link_state;
	writel(temp, port->addr);

	xhci_dbg(xhci, "Set port %d-%d link state, portsc: 0x%x, write 0x%x",
		 port->rhub->hcd->self.busnum, port->hcd_portnum + 1,
		 portsc, temp);
}