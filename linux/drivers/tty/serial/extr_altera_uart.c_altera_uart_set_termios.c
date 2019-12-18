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
struct uart_port {unsigned int uartclk; int /*<<< orphan*/  lock; } ;
struct ktermios {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_DIVISOR_REG ; 
 int /*<<< orphan*/  altera_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_termios_copy_hw (struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void altera_uart_set_termios(struct uart_port *port,
				    struct ktermios *termios,
				    struct ktermios *old)
{
	unsigned long flags;
	unsigned int baud, baudclk;

	baud = uart_get_baud_rate(port, termios, old, 0, 4000000);
	baudclk = port->uartclk / baud;

	if (old)
		tty_termios_copy_hw(termios, old);
	tty_termios_encode_baud_rate(termios, baud, baud);

	spin_lock_irqsave(&port->lock, flags);
	uart_update_timeout(port, termios->c_cflag, baud);
	altera_uart_writel(port, baudclk, ALTERA_UART_DIVISOR_REG);
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * FIXME: port->read_status_mask and port->ignore_status_mask
	 * need to be initialized based on termios settings for
	 * INPCK, IGNBRK, IGNPAR, PARMRK, BRKINT
	 */
}