#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  console; } ;
struct usb_serial_port {TYPE_1__ port; int /*<<< orphan*/  sysrq; } ;
struct urb {int actual_length; scalar_t__ transfer_buffer; struct usb_serial_port* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_1__*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  usb_serial_handle_sysrq_char (struct usb_serial_port*,char) ; 

void usb_serial_generic_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	char *ch = (char *)urb->transfer_buffer;
	int i;

	if (!urb->actual_length)
		return;
	/*
	 * The per character mucking around with sysrq path it too slow for
	 * stuff like 3G modems, so shortcircuit it in the 99.9999999% of
	 * cases where the USB serial is not a console anyway.
	 */
	if (!port->port.console || !port->sysrq) {
		tty_insert_flip_string(&port->port, ch, urb->actual_length);
	} else {
		for (i = 0; i < urb->actual_length; i++, ch++) {
			if (!usb_serial_handle_sysrq_char(port, *ch))
				tty_insert_flip_char(&port->port, *ch, TTY_NORMAL);
		}
	}
	tty_flip_buffer_push(&port->port);
}