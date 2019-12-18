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
struct usb_serial_port {int /*<<< orphan*/  write_fifo; int /*<<< orphan*/  port_number; int /*<<< orphan*/  minor; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int baud_base; void* closing_wait; void* close_delay; scalar_t__ custom_divisor; int /*<<< orphan*/  xmit_fifo_size; int /*<<< orphan*/  port; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 void* CLOSING_DELAY ; 
 int /*<<< orphan*/  PORT_16654 ; 
 int /*<<< orphan*/  kfifo_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int whiteheat_get_serial(struct tty_struct *tty,
				struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;

	ss->type = PORT_16654;
	ss->line = port->minor;
	ss->port = port->port_number;
	ss->xmit_fifo_size = kfifo_size(&port->write_fifo);
	ss->custom_divisor = 0;
	ss->baud_base = 460800;
	ss->close_delay = CLOSING_DELAY;
	ss->closing_wait = CLOSING_DELAY;

	return 0;
}