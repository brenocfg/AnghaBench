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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct keyspan_port_private {int break_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspan_send_setup (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void keyspan_break_ctl(struct tty_struct *tty, int break_state)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private 	*p_priv;

	p_priv = usb_get_serial_port_data(port);

	if (break_state == -1)
		p_priv->break_on = 1;
	else
		p_priv->break_on = 0;

	keyspan_send_setup(port, 0);
}