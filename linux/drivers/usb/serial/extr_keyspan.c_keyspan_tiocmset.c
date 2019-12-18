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
struct keyspan_port_private {int rts_state; int dtr_state; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  keyspan_send_setup (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int keyspan_tiocmset(struct tty_struct *tty,
			    unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private *p_priv = usb_get_serial_port_data(port);

	if (set & TIOCM_RTS)
		p_priv->rts_state = 1;
	if (set & TIOCM_DTR)
		p_priv->dtr_state = 1;
	if (clear & TIOCM_RTS)
		p_priv->rts_state = 0;
	if (clear & TIOCM_DTR)
		p_priv->dtr_state = 0;
	keyspan_send_setup(port, 0);
	return 0;
}