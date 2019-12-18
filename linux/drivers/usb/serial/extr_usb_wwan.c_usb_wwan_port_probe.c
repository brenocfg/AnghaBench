#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_wwan_port_private {struct usb_wwan_port_private** in_buffer; struct urb** in_urbs; struct usb_wwan_port_private** out_buffer; struct urb** out_urbs; int /*<<< orphan*/  delayed; } ;
typedef  struct usb_wwan_port_private u8 ;
struct usb_serial_port {int /*<<< orphan*/  bulk_out_endpointAddress; int /*<<< orphan*/  bulk_in_endpointAddress; int /*<<< orphan*/  bulk_out_size; int /*<<< orphan*/  bulk_in_size; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IN_BUFLEN ; 
 int N_IN_URB ; 
 int N_OUT_URB ; 
 int /*<<< orphan*/  OUT_BUFLEN ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_wwan_port_private*) ; 
 struct usb_wwan_port_private* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_wwan_port_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct usb_wwan_port_private*) ; 
 int /*<<< orphan*/  usb_wwan_indat_callback ; 
 int /*<<< orphan*/  usb_wwan_outdat_callback ; 
 struct urb* usb_wwan_setup_urb (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_serial_port*,struct usb_wwan_port_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usb_wwan_port_probe(struct usb_serial_port *port)
{
	struct usb_wwan_port_private *portdata;
	struct urb *urb;
	u8 *buffer;
	int i;

	if (!port->bulk_in_size || !port->bulk_out_size)
		return -ENODEV;

	portdata = kzalloc(sizeof(*portdata), GFP_KERNEL);
	if (!portdata)
		return -ENOMEM;

	init_usb_anchor(&portdata->delayed);

	for (i = 0; i < N_IN_URB; i++) {
		buffer = (u8 *)__get_free_page(GFP_KERNEL);
		if (!buffer)
			goto bail_out_error;
		portdata->in_buffer[i] = buffer;

		urb = usb_wwan_setup_urb(port, port->bulk_in_endpointAddress,
						USB_DIR_IN, port,
						buffer, IN_BUFLEN,
						usb_wwan_indat_callback);
		portdata->in_urbs[i] = urb;
	}

	for (i = 0; i < N_OUT_URB; i++) {
		buffer = kmalloc(OUT_BUFLEN, GFP_KERNEL);
		if (!buffer)
			goto bail_out_error2;
		portdata->out_buffer[i] = buffer;

		urb = usb_wwan_setup_urb(port, port->bulk_out_endpointAddress,
						USB_DIR_OUT, port,
						buffer, OUT_BUFLEN,
						usb_wwan_outdat_callback);
		portdata->out_urbs[i] = urb;
	}

	usb_set_serial_port_data(port, portdata);

	return 0;

bail_out_error2:
	for (i = 0; i < N_OUT_URB; i++) {
		usb_free_urb(portdata->out_urbs[i]);
		kfree(portdata->out_buffer[i]);
	}
bail_out_error:
	for (i = 0; i < N_IN_URB; i++) {
		usb_free_urb(portdata->in_urbs[i]);
		free_page((unsigned long)portdata->in_buffer[i]);
	}
	kfree(portdata);

	return -ENOMEM;
}