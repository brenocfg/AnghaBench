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
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct ktermios {int c_iflag; int c_cflag; } ;

/* Variables and functions */
 int CBAUD ; 
 int CREAD ; 
 int CS8 ; 
 int IGNPAR ; 
 int INPCK ; 
 int STAT_BRK_ERR ; 
 int STAT_FRM_ERR ; 
 int STAT_OVR_ERR ; 
 int STAT_PAR_ERR ; 
 int STAT_RX_RDY (struct uart_port*) ; 
 int STAT_TX_FIFO_FUL ; 
 int STAT_TX_RDY (struct uart_port*) ; 
 scalar_t__ mvebu_uart_baud_rate_set (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void mvebu_uart_set_termios(struct uart_port *port,
				   struct ktermios *termios,
				   struct ktermios *old)
{
	unsigned long flags;
	unsigned int baud;

	spin_lock_irqsave(&port->lock, flags);

	port->read_status_mask = STAT_RX_RDY(port) | STAT_OVR_ERR |
		STAT_TX_RDY(port) | STAT_TX_FIFO_FUL;

	if (termios->c_iflag & INPCK)
		port->read_status_mask |= STAT_FRM_ERR | STAT_PAR_ERR;

	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |=
			STAT_FRM_ERR | STAT_PAR_ERR | STAT_OVR_ERR;

	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= STAT_RX_RDY(port) | STAT_BRK_ERR;

	/*
	 * Maximum achievable frequency with simple baudrate divisor is 230400.
	 * Since the error per bit frame would be of more than 15%, achieving
	 * higher frequencies would require to implement the fractional divisor
	 * feature.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, 230400);
	if (mvebu_uart_baud_rate_set(port, baud)) {
		/* No clock available, baudrate cannot be changed */
		if (old)
			baud = uart_get_baud_rate(port, old, NULL, 0, 230400);
	} else {
		tty_termios_encode_baud_rate(termios, baud, baud);
		uart_update_timeout(port, termios->c_cflag, baud);
	}

	/* Only the following flag changes are supported */
	if (old) {
		termios->c_iflag &= INPCK | IGNPAR;
		termios->c_iflag |= old->c_iflag & ~(INPCK | IGNPAR);
		termios->c_cflag &= CREAD | CBAUD;
		termios->c_cflag |= old->c_cflag & ~(CREAD | CBAUD);
		termios->c_cflag |= CS8;
	}

	spin_unlock_irqrestore(&port->lock, flags);
}