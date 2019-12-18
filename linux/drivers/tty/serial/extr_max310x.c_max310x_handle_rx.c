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
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; scalar_t__ rx; int /*<<< orphan*/  buf_overrun; } ;
struct uart_port {unsigned int read_status_mask; unsigned int fifosize; unsigned int ignore_status_mask; TYPE_2__* state; TYPE_1__ icount; int /*<<< orphan*/  dev; } ;
struct max310x_one {unsigned int* rx_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned int MAX310X_LSR_FRERR_BIT ; 
 int /*<<< orphan*/  MAX310X_LSR_IRQSTS_REG ; 
 unsigned int MAX310X_LSR_RXBRK_BIT ; 
 unsigned int MAX310X_LSR_RXOVR_BIT ; 
 unsigned int MAX310X_LSR_RXPAR_BIT ; 
 int /*<<< orphan*/  MAX310X_RHR_REG ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  max310x_batch_read (struct uart_port*,unsigned int*,unsigned int) ; 
 unsigned int max310x_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct max310x_one* to_max310x_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void max310x_handle_rx(struct uart_port *port, unsigned int rxlen)
{
	struct max310x_one *one = to_max310x_port(port);
	unsigned int sts, ch, flag, i;

	if (port->read_status_mask == MAX310X_LSR_RXOVR_BIT) {
		/* We are just reading, happily ignoring any error conditions.
		 * Break condition, parity checking, framing errors -- they
		 * are all ignored. That means that we can do a batch-read.
		 *
		 * There is a small opportunity for race if the RX FIFO
		 * overruns while we're reading the buffer; the datasheets says
		 * that the LSR register applies to the "current" character.
		 * That's also the reason why we cannot do batched reads when
		 * asked to check the individual statuses.
		 * */

		sts = max310x_port_read(port, MAX310X_LSR_IRQSTS_REG);
		max310x_batch_read(port, one->rx_buf, rxlen);

		port->icount.rx += rxlen;
		flag = TTY_NORMAL;
		sts &= port->read_status_mask;

		if (sts & MAX310X_LSR_RXOVR_BIT) {
			dev_warn_ratelimited(port->dev, "Hardware RX FIFO overrun\n");
			port->icount.overrun++;
		}

		for (i = 0; i < (rxlen - 1); ++i)
			uart_insert_char(port, sts, 0, one->rx_buf[i], flag);

		/*
		 * Handle the overrun case for the last character only, since
		 * the RxFIFO overflow happens after it is pushed to the FIFO
		 * tail.
		 */
		uart_insert_char(port, sts, MAX310X_LSR_RXOVR_BIT,
				 one->rx_buf[rxlen-1], flag);

	} else {
		if (unlikely(rxlen >= port->fifosize)) {
			dev_warn_ratelimited(port->dev, "Possible RX FIFO overrun\n");
			port->icount.buf_overrun++;
			/* Ensure sanity of RX level */
			rxlen = port->fifosize;
		}

		while (rxlen--) {
			ch = max310x_port_read(port, MAX310X_RHR_REG);
			sts = max310x_port_read(port, MAX310X_LSR_IRQSTS_REG);

			sts &= MAX310X_LSR_RXPAR_BIT | MAX310X_LSR_FRERR_BIT |
			       MAX310X_LSR_RXOVR_BIT | MAX310X_LSR_RXBRK_BIT;

			port->icount.rx++;
			flag = TTY_NORMAL;

			if (unlikely(sts)) {
				if (sts & MAX310X_LSR_RXBRK_BIT) {
					port->icount.brk++;
					if (uart_handle_break(port))
						continue;
				} else if (sts & MAX310X_LSR_RXPAR_BIT)
					port->icount.parity++;
				else if (sts & MAX310X_LSR_FRERR_BIT)
					port->icount.frame++;
				else if (sts & MAX310X_LSR_RXOVR_BIT)
					port->icount.overrun++;

				sts &= port->read_status_mask;
				if (sts & MAX310X_LSR_RXBRK_BIT)
					flag = TTY_BREAK;
				else if (sts & MAX310X_LSR_RXPAR_BIT)
					flag = TTY_PARITY;
				else if (sts & MAX310X_LSR_FRERR_BIT)
					flag = TTY_FRAME;
				else if (sts & MAX310X_LSR_RXOVR_BIT)
					flag = TTY_OVERRUN;
			}

			if (uart_handle_sysrq_char(port, ch))
				continue;

			if (sts & port->ignore_status_mask)
				continue;

			uart_insert_char(port, sts, MAX310X_LSR_RXOVR_BIT, ch, flag);
		}
	}

	tty_flip_buffer_push(&port->state->port);
}