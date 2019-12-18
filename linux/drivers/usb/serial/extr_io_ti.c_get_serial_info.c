#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int baud_base; int close_delay; unsigned int closing_wait; int /*<<< orphan*/  xmit_fifo_size; scalar_t__ irq; int /*<<< orphan*/  port; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct edgeport_port {TYPE_2__* port; } ;
struct TYPE_3__ {unsigned int closing_wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  bulk_out_size; int /*<<< orphan*/  port_number; int /*<<< orphan*/  minor; TYPE_1__ port; } ;

/* Variables and functions */
 unsigned int ASYNC_CLOSING_WAIT_NONE ; 
 int HZ ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int jiffies_to_msecs (unsigned int) ; 
 struct edgeport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty,
				struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;
	struct edgeport_port *edge_port = usb_get_serial_port_data(port);
	unsigned cwait;

	cwait = edge_port->port->port.closing_wait;
	if (cwait != ASYNC_CLOSING_WAIT_NONE)
		cwait = jiffies_to_msecs(cwait) / 10;

	ss->type		= PORT_16550A;
	ss->line		= edge_port->port->minor;
	ss->port		= edge_port->port->port_number;
	ss->irq			= 0;
	ss->xmit_fifo_size	= edge_port->port->bulk_out_size;
	ss->baud_base		= 9600;
	ss->close_delay		= 5*HZ;
	ss->closing_wait	= cwait;
	return 0;
}