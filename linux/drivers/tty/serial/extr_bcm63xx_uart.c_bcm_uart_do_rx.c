#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; int /*<<< orphan*/  overrun; } ;
struct uart_port {unsigned int read_status_mask; unsigned int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int /*<<< orphan*/  UART_CTL_REG ; 
 unsigned int UART_CTL_RSTRXFIFO_MASK ; 
 unsigned int UART_FIFO_ANYERR_MASK ; 
 unsigned int UART_FIFO_BRKDET_MASK ; 
 unsigned int UART_FIFO_FRAMEERR_MASK ; 
 unsigned int UART_FIFO_PARERR_MASK ; 
 int /*<<< orphan*/  UART_FIFO_REG ; 
 int /*<<< orphan*/  UART_IR_REG ; 
 int /*<<< orphan*/  UART_IR_RXNOTEMPTY ; 
 int /*<<< orphan*/  UART_IR_RXOVER ; 
 unsigned int UART_IR_STAT (int /*<<< orphan*/ ) ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned int,char) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void bcm_uart_do_rx(struct uart_port *port)
{
	struct tty_port *tty_port = &port->state->port;
	unsigned int max_count;

	/* limit number of char read in interrupt, should not be
	 * higher than fifo size anyway since we're much faster than
	 * serial port */
	max_count = 32;
	do {
		unsigned int iestat, c, cstat;
		char flag;

		/* get overrun/fifo empty information from ier
		 * register */
		iestat = bcm_uart_readl(port, UART_IR_REG);

		if (unlikely(iestat & UART_IR_STAT(UART_IR_RXOVER))) {
			unsigned int val;

			/* fifo reset is required to clear
			 * interrupt */
			val = bcm_uart_readl(port, UART_CTL_REG);
			val |= UART_CTL_RSTRXFIFO_MASK;
			bcm_uart_writel(port, val, UART_CTL_REG);

			port->icount.overrun++;
			tty_insert_flip_char(tty_port, 0, TTY_OVERRUN);
		}

		if (!(iestat & UART_IR_STAT(UART_IR_RXNOTEMPTY)))
			break;

		cstat = c = bcm_uart_readl(port, UART_FIFO_REG);
		port->icount.rx++;
		flag = TTY_NORMAL;
		c &= 0xff;

		if (unlikely((cstat & UART_FIFO_ANYERR_MASK))) {
			/* do stats first */
			if (cstat & UART_FIFO_BRKDET_MASK) {
				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			}

			if (cstat & UART_FIFO_PARERR_MASK)
				port->icount.parity++;
			if (cstat & UART_FIFO_FRAMEERR_MASK)
				port->icount.frame++;

			/* update flag wrt read_status_mask */
			cstat &= port->read_status_mask;
			if (cstat & UART_FIFO_BRKDET_MASK)
				flag = TTY_BREAK;
			if (cstat & UART_FIFO_FRAMEERR_MASK)
				flag = TTY_FRAME;
			if (cstat & UART_FIFO_PARERR_MASK)
				flag = TTY_PARITY;
		}

		if (uart_handle_sysrq_char(port, c))
			continue;


		if ((cstat & port->ignore_status_mask) == 0)
			tty_insert_flip_char(tty_port, c, flag);

	} while (--max_count);

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tty_port);
	spin_lock(&port->lock);
}