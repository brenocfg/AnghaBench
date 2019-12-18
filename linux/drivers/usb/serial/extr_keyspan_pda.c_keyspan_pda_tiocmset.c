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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int keyspan_pda_get_modem_info (struct usb_serial*,unsigned char*) ; 
 int keyspan_pda_set_modem_info (struct usb_serial*,unsigned char) ; 

__attribute__((used)) static int keyspan_pda_tiocmset(struct tty_struct *tty,
				unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct usb_serial *serial = port->serial;
	int rc;
	unsigned char status;

	rc = keyspan_pda_get_modem_info(serial, &status);
	if (rc < 0)
		return rc;

	if (set & TIOCM_RTS)
		status |= (1<<2);
	if (set & TIOCM_DTR)
		status |= (1<<7);

	if (clear & TIOCM_RTS)
		status &= ~(1<<2);
	if (clear & TIOCM_DTR)
		status &= ~(1<<7);
	rc = keyspan_pda_set_modem_info(serial, status);
	return rc;
}