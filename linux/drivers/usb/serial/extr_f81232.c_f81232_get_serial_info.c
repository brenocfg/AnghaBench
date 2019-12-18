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
struct usb_serial_port {int /*<<< orphan*/  port_number; int /*<<< orphan*/  minor; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int /*<<< orphan*/  baud_base; int /*<<< orphan*/  port; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct f81232_private {int /*<<< orphan*/  baud_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_16550A ; 
 struct f81232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int f81232_get_serial_info(struct tty_struct *tty,
		struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;
	struct f81232_private *priv = usb_get_serial_port_data(port);

	ss->type = PORT_16550A;
	ss->line = port->minor;
	ss->port = port->port_number;
	ss->baud_base = priv->baud_base;
	return 0;
}