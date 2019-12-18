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
struct ftdi_private {int last_dtr_rts; } ;

/* Variables and functions */
 unsigned char FTDI_SIO_CTS_MASK ; 
 unsigned char FTDI_SIO_DSR_MASK ; 
 unsigned char FTDI_SIO_RI_MASK ; 
 unsigned char FTDI_SIO_RLSD_MASK ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_RI ; 
 int ftdi_get_modem_status (struct usb_serial_port*,unsigned char*) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int ftdi_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	unsigned char buf[2];
	int ret;

	ret = ftdi_get_modem_status(port, buf);
	if (ret < 0)
		return ret;

	ret =	(buf[0] & FTDI_SIO_DSR_MASK  ? TIOCM_DSR : 0) |
		(buf[0] & FTDI_SIO_CTS_MASK  ? TIOCM_CTS : 0) |
		(buf[0] & FTDI_SIO_RI_MASK   ? TIOCM_RI  : 0) |
		(buf[0] & FTDI_SIO_RLSD_MASK ? TIOCM_CD  : 0) |
		priv->last_dtr_rts;

	return ret;
}