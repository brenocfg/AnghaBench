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
struct TYPE_2__ {int close_delay; int closing_wait; int /*<<< orphan*/  tty; } ;
struct usb_serial_port {TYPE_1__ port; int /*<<< orphan*/  port_number; int /*<<< orphan*/  minor; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int close_delay; int closing_wait; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  port; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int ASYNC_CLOSING_WAIT_NONE ; 
 int /*<<< orphan*/  tty_get_baud_rate (int /*<<< orphan*/ ) ; 

int usb_wwan_get_serial_info(struct tty_struct *tty,
			   struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;

	ss->line            = port->minor;
	ss->port            = port->port_number;
	ss->baud_base       = tty_get_baud_rate(port->port.tty);
	ss->close_delay	    = port->port.close_delay / 10;
	ss->closing_wait    = port->port.closing_wait == ASYNC_CLOSING_WAIT_NONE ?
				 ASYNC_CLOSING_WAIT_NONE :
				 port->port.closing_wait / 10;
	return 0;
}