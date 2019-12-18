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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; int /*<<< orphan*/  overrun; } ;
struct uart_port {int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct pic32_sport {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_UART_RX ; 
 unsigned int PIC32_UART_RX_FIFO_DEPTH ; 
 int /*<<< orphan*/  PIC32_UART_STA ; 
 int PIC32_UART_STA_FERR ; 
 int PIC32_UART_STA_OERR ; 
 int PIC32_UART_STA_PERR ; 
 int PIC32_UART_STA_URXDA ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int pic32_uart_readl (struct pic32_sport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_uart_writel (struct pic32_sport*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int,char) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pic32_uart_do_rx(struct uart_port *port)
{
	struct pic32_sport *sport = to_pic32_sport(port);
	struct tty_port *tty;
	unsigned int max_count;

	/* limit number of char read in interrupt, should not be
	 * higher than fifo size anyway since we're much faster than
	 * serial port
	 */
	max_count = PIC32_UART_RX_FIFO_DEPTH;

	spin_lock(&port->lock);

	tty = &port->state->port;

	do {
		u32 sta_reg, c;
		char flag;

		/* get overrun/fifo empty information from status register */
		sta_reg = pic32_uart_readl(sport, PIC32_UART_STA);
		if (unlikely(sta_reg & PIC32_UART_STA_OERR)) {

			/* fifo reset is required to clear interrupt */
			pic32_uart_writel(sport, PIC32_CLR(PIC32_UART_STA),
						PIC32_UART_STA_OERR);

			port->icount.overrun++;
			tty_insert_flip_char(tty, 0, TTY_OVERRUN);
		}

		/* Can at least one more character can be read? */
		if (!(sta_reg & PIC32_UART_STA_URXDA))
			break;

		/* read the character and increment the rx counter */
		c = pic32_uart_readl(sport, PIC32_UART_RX);

		port->icount.rx++;
		flag = TTY_NORMAL;
		c &= 0xff;

		if (unlikely((sta_reg & PIC32_UART_STA_PERR) ||
			     (sta_reg & PIC32_UART_STA_FERR))) {

			/* do stats first */
			if (sta_reg & PIC32_UART_STA_PERR)
				port->icount.parity++;
			if (sta_reg & PIC32_UART_STA_FERR)
				port->icount.frame++;

			/* update flag wrt read_status_mask */
			sta_reg &= port->read_status_mask;

			if (sta_reg & PIC32_UART_STA_FERR)
				flag = TTY_FRAME;
			if (sta_reg & PIC32_UART_STA_PERR)
				flag = TTY_PARITY;
		}

		if (uart_handle_sysrq_char(port, c))
			continue;

		if ((sta_reg & port->ignore_status_mask) == 0)
			tty_insert_flip_char(tty, c, flag);

	} while (--max_count);

	spin_unlock(&port->lock);

	tty_flip_buffer_push(tty);
}