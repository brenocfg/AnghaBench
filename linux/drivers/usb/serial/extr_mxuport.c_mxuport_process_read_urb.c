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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {struct usb_serial_port** port; } ;
struct urb {struct usb_serial_port* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxuport_process_read_urb_demux_data (struct urb*) ; 
 int /*<<< orphan*/  mxuport_process_read_urb_demux_event (struct urb*) ; 

__attribute__((used)) static void mxuport_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	struct usb_serial *serial = port->serial;

	if (port == serial->port[0])
		mxuport_process_read_urb_demux_data(urb);

	if (port == serial->port[1])
		mxuport_process_read_urb_demux_event(urb);
}