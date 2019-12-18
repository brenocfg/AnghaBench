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
typedef  size_t u16 ;
struct xhci_port {int /*<<< orphan*/  addr; } ;
struct xhci_hub {struct xhci_port** ports; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  root_hub; int /*<<< orphan*/  busnum; } ;
struct usb_hcd {TYPE_1__ self; } ;

/* Variables and functions */
 int PORT_POWER ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_acpi_power_manageable (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  usb_acpi_set_power_state (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,size_t,char*,int) ; 
 struct xhci_hub* xhci_get_rhub (struct usb_hcd*) ; 
 int xhci_port_state_to_neutral (int) ; 

__attribute__((used)) static void xhci_set_port_power(struct xhci_hcd *xhci, struct usb_hcd *hcd,
				u16 index, bool on, unsigned long *flags)
{
	struct xhci_hub *rhub;
	struct xhci_port *port;
	u32 temp;

	rhub = xhci_get_rhub(hcd);
	port = rhub->ports[index];
	temp = readl(port->addr);

	xhci_dbg(xhci, "set port power %d-%d %s, portsc: 0x%x\n",
		 hcd->self.busnum, index + 1, on ? "ON" : "OFF", temp);

	temp = xhci_port_state_to_neutral(temp);

	if (on) {
		/* Power on */
		writel(temp | PORT_POWER, port->addr);
		readl(port->addr);
	} else {
		/* Power off */
		writel(temp & ~PORT_POWER, port->addr);
	}

	spin_unlock_irqrestore(&xhci->lock, *flags);
	temp = usb_acpi_power_manageable(hcd->self.root_hub,
					index);
	if (temp)
		usb_acpi_set_power_state(hcd->self.root_hub,
			index, on);
	spin_lock_irqsave(&xhci->lock, *flags);
}