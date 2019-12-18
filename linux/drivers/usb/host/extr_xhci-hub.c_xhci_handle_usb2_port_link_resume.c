#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct xhci_port {size_t hcd_portnum; int /*<<< orphan*/  addr; TYPE_1__* rhub; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; } ;
struct xhci_bus_state {unsigned long* resume_done; int port_c_suspend; int suspended_ports; int /*<<< orphan*/  rexit_ports; int /*<<< orphan*/ * rexit_done; int /*<<< orphan*/  resuming_ports; } ;
struct TYPE_5__ {int /*<<< orphan*/  busnum; } ;
struct usb_hcd {TYPE_2__ self; int /*<<< orphan*/  rh_timer; } ;
struct TYPE_4__ {struct xhci_bus_state bus_state; struct usb_hcd* hcd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t PORT_PE ; 
 int /*<<< orphan*/  PORT_PLC ; 
 size_t PORT_RESET ; 
 size_t USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  USB_RESUME_TIMEOUT ; 
 int /*<<< orphan*/  XDEV_U0 ; 
 int /*<<< orphan*/  XHCI_MAX_REXIT_TIMEOUT_MS ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ *) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usb_hcd_end_port_resume (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  usb_hcd_start_port_resume (TYPE_2__*,size_t) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 int xhci_find_slot_id_by_port (struct usb_hcd*,struct xhci_hcd*,size_t) ; 
 int /*<<< orphan*/  xhci_ring_device (struct xhci_hcd*,int) ; 
 int /*<<< orphan*/  xhci_set_link_state (struct xhci_hcd*,struct xhci_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_test_and_clear_bit (struct xhci_hcd*,struct xhci_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static int xhci_handle_usb2_port_link_resume(struct xhci_port *port,
					     u32 *status, u32 portsc,
					     unsigned long flags)
{
	struct xhci_bus_state *bus_state;
	struct xhci_hcd	*xhci;
	struct usb_hcd *hcd;
	int slot_id;
	u32 wIndex;

	hcd = port->rhub->hcd;
	bus_state = &port->rhub->bus_state;
	xhci = hcd_to_xhci(hcd);
	wIndex = port->hcd_portnum;

	if ((portsc & PORT_RESET) || !(portsc & PORT_PE)) {
		*status = 0xffffffff;
		return -EINVAL;
	}
	/* did port event handler already start resume timing? */
	if (!bus_state->resume_done[wIndex]) {
		/* If not, maybe we are in a host initated resume? */
		if (test_bit(wIndex, &bus_state->resuming_ports)) {
			/* Host initated resume doesn't time the resume
			 * signalling using resume_done[].
			 * It manually sets RESUME state, sleeps 20ms
			 * and sets U0 state. This should probably be
			 * changed, but not right now.
			 */
		} else {
			/* port resume was discovered now and here,
			 * start resume timing
			 */
			unsigned long timeout = jiffies +
				msecs_to_jiffies(USB_RESUME_TIMEOUT);

			set_bit(wIndex, &bus_state->resuming_ports);
			bus_state->resume_done[wIndex] = timeout;
			mod_timer(&hcd->rh_timer, timeout);
			usb_hcd_start_port_resume(&hcd->self, wIndex);
		}
	/* Has resume been signalled for USB_RESUME_TIME yet? */
	} else if (time_after_eq(jiffies, bus_state->resume_done[wIndex])) {
		int time_left;

		xhci_dbg(xhci, "resume USB2 port %d-%d\n",
			 hcd->self.busnum, wIndex + 1);

		bus_state->resume_done[wIndex] = 0;
		clear_bit(wIndex, &bus_state->resuming_ports);

		set_bit(wIndex, &bus_state->rexit_ports);

		xhci_test_and_clear_bit(xhci, port, PORT_PLC);
		xhci_set_link_state(xhci, port, XDEV_U0);

		spin_unlock_irqrestore(&xhci->lock, flags);
		time_left = wait_for_completion_timeout(
			&bus_state->rexit_done[wIndex],
			msecs_to_jiffies(XHCI_MAX_REXIT_TIMEOUT_MS));
		spin_lock_irqsave(&xhci->lock, flags);

		if (time_left) {
			slot_id = xhci_find_slot_id_by_port(hcd, xhci,
							    wIndex + 1);
			if (!slot_id) {
				xhci_dbg(xhci, "slot_id is zero\n");
				*status = 0xffffffff;
				return -ENODEV;
			}
			xhci_ring_device(xhci, slot_id);
		} else {
			int port_status = readl(port->addr);

			xhci_warn(xhci, "Port resume timed out, port %d-%d: 0x%x\n",
				  hcd->self.busnum, wIndex + 1, port_status);
			*status |= USB_PORT_STAT_SUSPEND;
			clear_bit(wIndex, &bus_state->rexit_ports);
		}

		usb_hcd_end_port_resume(&hcd->self, wIndex);
		bus_state->port_c_suspend |= 1 << wIndex;
		bus_state->suspended_ports &= ~(1 << wIndex);
	} else {
		/*
		 * The resume has been signaling for less than
		 * USB_RESUME_TIME. Report the port status as SUSPEND,
		 * let the usbcore check port status again and clear
		 * resume signaling later.
		 */
		*status |= USB_PORT_STAT_SUSPEND;
	}
	return 0;
}