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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct moschip_port {unsigned int shadowMCR; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int MCR_DTR ; 
 unsigned int MCR_LOOPBACK ; 
 unsigned int MCR_RTS ; 
 int /*<<< orphan*/  MODEM_CONTROL_REGISTER ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct moschip_port* mos7840_get_port_private (struct usb_serial_port*) ; 
 int mos7840_set_uart_reg (struct usb_serial_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mos7840_tiocmset(struct tty_struct *tty,
			    unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct moschip_port *mos7840_port;
	unsigned int mcr;
	int status;

	mos7840_port = mos7840_get_port_private(port);

	if (mos7840_port == NULL)
		return -ENODEV;

	/* FIXME: What locks the port registers ? */
	mcr = mos7840_port->shadowMCR;
	if (clear & TIOCM_RTS)
		mcr &= ~MCR_RTS;
	if (clear & TIOCM_DTR)
		mcr &= ~MCR_DTR;
	if (clear & TIOCM_LOOP)
		mcr &= ~MCR_LOOPBACK;

	if (set & TIOCM_RTS)
		mcr |= MCR_RTS;
	if (set & TIOCM_DTR)
		mcr |= MCR_DTR;
	if (set & TIOCM_LOOP)
		mcr |= MCR_LOOPBACK;

	mos7840_port->shadowMCR = mcr;

	status = mos7840_set_uart_reg(port, MODEM_CONTROL_REGISTER, mcr);
	if (status < 0) {
		dev_dbg(&port->dev, "setting MODEM_CONTROL_REGISTER Failed\n");
		return status;
	}

	return 0;
}