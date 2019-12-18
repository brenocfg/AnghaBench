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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  uartclk; } ;
struct ktermios {int c_cflag; } ;

/* Variables and functions */
 int CMSPAR ; 
 int CRTSCTS ; 
 int CS8 ; 
 int CSIZE ; 
 int CSTOPB ; 
 unsigned int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned int) ; 
 int PARENB ; 
 int /*<<< orphan*/  UARTn_BAUDDIV ; 
 unsigned int UARTn_BAUDDIV_MASK ; 
 int /*<<< orphan*/  mps2_uart_write32 (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
mps2_uart_set_termios(struct uart_port *port, struct ktermios *termios,
		      struct ktermios *old)
{
	unsigned long flags;
	unsigned int baud, bauddiv;

	termios->c_cflag &= ~(CRTSCTS | CMSPAR);
	termios->c_cflag &= ~CSIZE;
	termios->c_cflag |= CS8;
	termios->c_cflag &= ~PARENB;
	termios->c_cflag &= ~CSTOPB;

	baud = uart_get_baud_rate(port, termios, old,
			DIV_ROUND_CLOSEST(port->uartclk, UARTn_BAUDDIV_MASK),
			DIV_ROUND_CLOSEST(port->uartclk, 16));

	bauddiv = DIV_ROUND_CLOSEST(port->uartclk, baud);

	spin_lock_irqsave(&port->lock, flags);

	uart_update_timeout(port, termios->c_cflag, baud);
	mps2_uart_write32(port, bauddiv, UARTn_BAUDDIV);

	spin_unlock_irqrestore(&port->lock, flags);

	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
}