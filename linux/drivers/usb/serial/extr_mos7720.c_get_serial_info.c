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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int xmit_fifo_size; int baud_base; int close_delay; int closing_wait; scalar_t__ irq; int /*<<< orphan*/  port; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct moschip_port {TYPE_1__* port; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_number; int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int HZ ; 
 int NUM_URBS ; 
 int /*<<< orphan*/  PORT_16550A ; 
 int URB_TRANSFER_BUFFER_SIZE ; 
 struct moschip_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty,
			   struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;
	struct moschip_port *mos7720_port = usb_get_serial_port_data(port);

	ss->type		= PORT_16550A;
	ss->line		= mos7720_port->port->minor;
	ss->port		= mos7720_port->port->port_number;
	ss->irq			= 0;
	ss->xmit_fifo_size	= NUM_URBS * URB_TRANSFER_BUFFER_SIZE;
	ss->baud_base		= 9600;
	ss->close_delay		= 5*HZ;
	ss->closing_wait	= 30*HZ;
	return 0;
}