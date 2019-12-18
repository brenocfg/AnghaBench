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
struct uart_port {int uartclk; int /*<<< orphan*/  lock; int /*<<< orphan*/  ignore_status_mask; } ;
struct rp2_uart_port {int dummy; } ;
struct ktermios {int c_cflag; int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
 int CREAD ; 
 int /*<<< orphan*/  RP2_DUMMY_READ ; 
 int /*<<< orphan*/  __rp2_uart_set_termios (struct rp2_uart_port*,int,int /*<<< orphan*/ ,unsigned int) ; 
 struct rp2_uart_port* port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void rp2_uart_set_termios(struct uart_port *port,
				 struct ktermios *new,
				 struct ktermios *old)
{
	struct rp2_uart_port *up = port_to_up(port);
	unsigned long flags;
	unsigned int baud, baud_div;

	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	baud_div = uart_get_divisor(port, baud);

	if (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	spin_lock_irqsave(&port->lock, flags);

	/* ignore all characters if CREAD is not set */
	port->ignore_status_mask = (new->c_cflag & CREAD) ? 0 : RP2_DUMMY_READ;

	__rp2_uart_set_termios(up, new->c_cflag, new->c_iflag, baud_div);
	uart_update_timeout(port, new->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
}