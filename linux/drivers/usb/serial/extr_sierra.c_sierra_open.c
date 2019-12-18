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
struct usb_serial_port {int bulk_in_endpointAddress; struct usb_serial* serial; } ;
struct usb_serial {TYPE_1__* interface; int /*<<< orphan*/  dev; } ;
struct urb {int dummy; } ;
struct tty_struct {int dummy; } ;
struct sierra_port_private {int num_in_urbs; struct urb** in_urbs; } ;
struct sierra_intf_private {int open_ports; int /*<<< orphan*/  susp_lock; } ;
struct TYPE_2__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IN_BUFLEN ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  sierra_indat_callback ; 
 int /*<<< orphan*/  sierra_release_urb (struct urb*) ; 
 struct urb* sierra_setup_urb (struct usb_serial*,int,int,struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sierra_stop_rx_urbs (struct usb_serial_port*) ; 
 int sierra_submit_rx_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int) ; 
 struct sierra_intf_private* usb_get_serial_data (struct usb_serial*) ; 
 struct sierra_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sierra_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	struct sierra_port_private *portdata;
	struct usb_serial *serial = port->serial;
	struct sierra_intf_private *intfdata = usb_get_serial_data(serial);
	int i;
	int err;
	int endpoint;
	struct urb *urb;

	portdata = usb_get_serial_port_data(port);

	endpoint = port->bulk_in_endpointAddress;
	for (i = 0; i < portdata->num_in_urbs; i++) {
		urb = sierra_setup_urb(serial, endpoint, USB_DIR_IN, port,
					IN_BUFLEN, GFP_KERNEL,
					sierra_indat_callback);
		portdata->in_urbs[i] = urb;
	}
	/* clear halt condition */
	usb_clear_halt(serial->dev,
			usb_sndbulkpipe(serial->dev, endpoint) | USB_DIR_IN);

	err = sierra_submit_rx_urbs(port, GFP_KERNEL);
	if (err)
		goto err_submit;

	spin_lock_irq(&intfdata->susp_lock);
	if (++intfdata->open_ports == 1)
		serial->interface->needs_remote_wakeup = 1;
	spin_unlock_irq(&intfdata->susp_lock);
	usb_autopm_put_interface(serial->interface);

	return 0;

err_submit:
	sierra_stop_rx_urbs(port);

	for (i = 0; i < portdata->num_in_urbs; i++) {
		sierra_release_urb(portdata->in_urbs[i]);
		portdata->in_urbs[i] = NULL;
	}

	return err;
}