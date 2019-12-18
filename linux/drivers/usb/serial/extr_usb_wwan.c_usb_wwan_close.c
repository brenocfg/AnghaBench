#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_wwan_port_private {int /*<<< orphan*/ * out_urbs; int /*<<< orphan*/ * in_urbs; int /*<<< orphan*/  delayed; } ;
struct usb_wwan_intf_private {scalar_t__ open_ports; int /*<<< orphan*/  susp_lock; } ;
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; struct usb_serial* serial; } ;
struct usb_serial {TYPE_1__* interface; } ;
struct urb {int dummy; } ;
struct TYPE_3__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 int N_IN_URB ; 
 int N_OUT_URB ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbusy_queued_urb (struct urb*,struct usb_wwan_port_private*) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (TYPE_1__*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 struct usb_wwan_intf_private* usb_get_serial_data (struct usb_serial*) ; 
 struct usb_wwan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void usb_wwan_close(struct usb_serial_port *port)
{
	int i;
	struct usb_serial *serial = port->serial;
	struct usb_wwan_port_private *portdata;
	struct usb_wwan_intf_private *intfdata = usb_get_serial_data(serial);
	struct urb *urb;

	portdata = usb_get_serial_port_data(port);

	/*
	 * Need to take susp_lock to make sure port is not already being
	 * resumed, but no need to hold it due to initialized
	 */
	spin_lock_irq(&intfdata->susp_lock);
	if (--intfdata->open_ports == 0)
		serial->interface->needs_remote_wakeup = 0;
	spin_unlock_irq(&intfdata->susp_lock);

	for (;;) {
		urb = usb_get_from_anchor(&portdata->delayed);
		if (!urb)
			break;
		unbusy_queued_urb(urb, portdata);
		usb_autopm_put_interface_async(serial->interface);
	}

	for (i = 0; i < N_IN_URB; i++)
		usb_kill_urb(portdata->in_urbs[i]);
	for (i = 0; i < N_OUT_URB; i++)
		usb_kill_urb(portdata->out_urbs[i]);
	usb_kill_urb(port->interrupt_in_urb);

	usb_autopm_get_interface_no_resume(serial->interface);
}