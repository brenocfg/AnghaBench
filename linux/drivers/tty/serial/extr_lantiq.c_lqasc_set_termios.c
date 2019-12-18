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
struct uart_port {int read_status_mask; int ignore_status_mask; int uartclk; scalar_t__ membase; } ;
struct ltq_uart_port {int /*<<< orphan*/  lock; } ;
struct ktermios {unsigned int c_cflag; unsigned int c_iflag; } ;

/* Variables and functions */
 unsigned int ASCCON_BRS ; 
 unsigned int ASCCON_FDE ; 
 unsigned int ASCCON_FEN ; 
 unsigned int ASCCON_M_7ASYNC ; 
 unsigned int ASCCON_M_8ASYNC ; 
 unsigned int ASCCON_ODD ; 
 unsigned int ASCCON_R ; 
 unsigned int ASCCON_ROEN ; 
 unsigned int ASCCON_STP ; 
 unsigned int ASCCON_TOEN ; 
 int ASCSTATE_FE ; 
 int ASCSTATE_PE ; 
 int ASCSTATE_ROE ; 
 unsigned int ASCWHBSTATE_SETREN ; 
 unsigned int CMSPAR ; 
 unsigned int CREAD ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 unsigned int CS8 ; 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 unsigned int IGNBRK ; 
 unsigned int IGNPAR ; 
 unsigned int INPCK ; 
 scalar_t__ LTQ_ASC_BG ; 
 scalar_t__ LTQ_ASC_CON ; 
 scalar_t__ LTQ_ASC_WHBSTATE ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 int UART_DUMMY_UER_RX ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  asc_update_bits (unsigned int,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
lqasc_set_termios(struct uart_port *port,
	struct ktermios *new, struct ktermios *old)
{
	unsigned int cflag;
	unsigned int iflag;
	unsigned int divisor;
	unsigned int baud;
	unsigned int con = 0;
	unsigned long flags;
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	cflag = new->c_cflag;
	iflag = new->c_iflag;

	switch (cflag & CSIZE) {
	case CS7:
		con = ASCCON_M_7ASYNC;
		break;

	case CS5:
	case CS6:
	default:
		new->c_cflag &= ~ CSIZE;
		new->c_cflag |= CS8;
		con = ASCCON_M_8ASYNC;
		break;
	}

	cflag &= ~CMSPAR; /* Mark/Space parity is not supported */

	if (cflag & CSTOPB)
		con |= ASCCON_STP;

	if (cflag & PARENB) {
		if (!(cflag & PARODD))
			con &= ~ASCCON_ODD;
		else
			con |= ASCCON_ODD;
	}

	port->read_status_mask = ASCSTATE_ROE;
	if (iflag & INPCK)
		port->read_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	port->ignore_status_mask = 0;
	if (iflag & IGNPAR)
		port->ignore_status_mask |= ASCSTATE_FE | ASCSTATE_PE;

	if (iflag & IGNBRK) {
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (iflag & IGNPAR)
			port->ignore_status_mask |= ASCSTATE_ROE;
	}

	if ((cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_DUMMY_UER_RX;

	/* set error signals  - framing, parity  and overrun, enable receiver */
	con |= ASCCON_FEN | ASCCON_TOEN | ASCCON_ROEN;

	spin_lock_irqsave(&ltq_port->lock, flags);

	/* set up CON */
	asc_update_bits(0, con, port->membase + LTQ_ASC_CON);

	/* Set baud rate - take a divider of 2 into account */
	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	divisor = uart_get_divisor(port, baud);
	divisor = divisor / 2 - 1;

	/* disable the baudrate generator */
	asc_update_bits(ASCCON_R, 0, port->membase + LTQ_ASC_CON);

	/* make sure the fractional divider is off */
	asc_update_bits(ASCCON_FDE, 0, port->membase + LTQ_ASC_CON);

	/* set up to use divisor of 2 */
	asc_update_bits(ASCCON_BRS, 0, port->membase + LTQ_ASC_CON);

	/* now we can write the new baudrate into the register */
	__raw_writel(divisor, port->membase + LTQ_ASC_BG);

	/* turn the baudrate generator back on */
	asc_update_bits(0, ASCCON_R, port->membase + LTQ_ASC_CON);

	/* enable rx */
	__raw_writel(ASCWHBSTATE_SETREN, port->membase + LTQ_ASC_WHBSTATE);

	spin_unlock_irqrestore(&ltq_port->lock, flags);

	/* Don't rewrite B0 */
	if (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	uart_update_timeout(port, cflag, baud);
}