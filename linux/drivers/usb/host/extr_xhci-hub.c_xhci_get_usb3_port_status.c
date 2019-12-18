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
typedef  int u32 ;
struct xhci_port {int hcd_portnum; TYPE_1__* rhub; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_bus_state {int suspended_ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcd; struct xhci_bus_state bus_state; } ;

/* Variables and functions */
 int PORT_CEC ; 
 int PORT_PLC ; 
 int PORT_PLS_MASK ; 
 int PORT_POWER ; 
 int PORT_WRC ; 
 int USB_PORT_STAT_C_BH_RESET ; 
 int USB_PORT_STAT_C_CONFIG_ERROR ; 
 int USB_PORT_STAT_C_LINK_STATE ; 
 int USB_SS_PORT_STAT_POWER ; 
 int XDEV_RESUME ; 
 int XDEV_U0 ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_del_comp_mod_timer (struct xhci_hcd*,int,int) ; 
 int /*<<< orphan*/  xhci_hub_report_usb3_link_state (struct xhci_hcd*,int*,int) ; 

__attribute__((used)) static void xhci_get_usb3_port_status(struct xhci_port *port, u32 *status,
				      u32 portsc)
{
	struct xhci_bus_state *bus_state;
	struct xhci_hcd	*xhci;
	u32 link_state;
	u32 portnum;

	bus_state = &port->rhub->bus_state;
	xhci = hcd_to_xhci(port->rhub->hcd);
	link_state = portsc & PORT_PLS_MASK;
	portnum = port->hcd_portnum;

	/* USB3 specific wPortChange bits
	 *
	 * Port link change with port in resume state should not be
	 * reported to usbcore, as this is an internal state to be
	 * handled by xhci driver. Reporting PLC to usbcore may
	 * cause usbcore clearing PLC first and port change event
	 * irq won't be generated.
	 */

	if (portsc & PORT_PLC && (link_state != XDEV_RESUME))
		*status |= USB_PORT_STAT_C_LINK_STATE << 16;
	if (portsc & PORT_WRC)
		*status |= USB_PORT_STAT_C_BH_RESET << 16;
	if (portsc & PORT_CEC)
		*status |= USB_PORT_STAT_C_CONFIG_ERROR << 16;

	/* USB3 specific wPortStatus bits */
	if (portsc & PORT_POWER) {
		*status |= USB_SS_PORT_STAT_POWER;
		/* link state handling */
		if (link_state == XDEV_U0)
			bus_state->suspended_ports &= ~(1 << portnum);
	}

	xhci_hub_report_usb3_link_state(xhci, status, portsc);
	xhci_del_comp_mod_timer(xhci, portsc, portnum);
}