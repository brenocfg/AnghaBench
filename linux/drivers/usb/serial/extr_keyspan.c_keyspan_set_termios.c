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
struct usb_serial_port {int port_number; } ;
struct TYPE_2__ {unsigned int c_cflag; } ;
struct tty_struct {TYPE_1__ termios; } ;
struct ktermios {int dummy; } ;
struct keyspan_port_private {int baud; unsigned int cflag; int /*<<< orphan*/  flow_control; struct keyspan_device_details* device_details; } ;
struct keyspan_device_details {scalar_t__ (* calculate_baud_rate ) (struct usb_serial_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  baudclk; } ;

/* Variables and functions */
 unsigned int CMSPAR ; 
 unsigned int CRTSCTS ; 
 scalar_t__ KEYSPAN_BAUD_RATE_OK ; 
 int /*<<< orphan*/  flow_cts ; 
 int /*<<< orphan*/  flow_none ; 
 int /*<<< orphan*/  keyspan_send_setup (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct usb_serial_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int,int) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int tty_termios_baud_rate (struct ktermios*) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void keyspan_set_termios(struct tty_struct *tty,
		struct usb_serial_port *port, struct ktermios *old_termios)
{
	int				baud_rate, device_port;
	struct keyspan_port_private 	*p_priv;
	const struct keyspan_device_details	*d_details;
	unsigned int 			cflag;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;
	cflag = tty->termios.c_cflag;
	device_port = port->port_number;

	/* Baud rate calculation takes baud rate as an integer
	   so other rates can be generated if desired. */
	baud_rate = tty_get_baud_rate(tty);
	/* If no match or invalid, don't change */
	if (d_details->calculate_baud_rate(port, baud_rate, d_details->baudclk,
				NULL, NULL, NULL, device_port) == KEYSPAN_BAUD_RATE_OK) {
		/* FIXME - more to do here to ensure rate changes cleanly */
		/* FIXME - calculate exact rate from divisor ? */
		p_priv->baud = baud_rate;
	} else
		baud_rate = tty_termios_baud_rate(old_termios);

	tty_encode_baud_rate(tty, baud_rate, baud_rate);
	/* set CTS/RTS handshake etc. */
	p_priv->cflag = cflag;
	p_priv->flow_control = (cflag & CRTSCTS) ? flow_cts : flow_none;

	/* Mark/Space not supported */
	tty->termios.c_cflag &= ~CMSPAR;

	keyspan_send_setup(port, 0);
}