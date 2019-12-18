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

/* Variables and functions */
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_1__*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  usb_serial_handle_sysrq_char (struct usb_serial_port*,char) ; 

__attribute__((used)) static void mxuport_process_read_urb_data(struct usb_serial_port *port,
					  char *data, int size)
{
	int i;

	if (!port->port.console || !port->sysrq) {
		tty_insert_flip_string(&port->port, data, size);
	} else {
		for (i = 0; i < size; i++, data++) {
			if (!usb_serial_handle_sysrq_char(port, *data))
				tty_insert_flip_char(&port->port, *data,
						     TTY_NORMAL);
		}
	}
	tty_flip_buffer_push(&port->port);
}