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
struct TYPE_4__ {int /*<<< orphan*/  tx; } ;
struct uart_port {unsigned int fifosize; scalar_t__ membase; TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 unsigned int STAT_TX_FIFO_FUL ; 
 scalar_t__ UART_STAT ; 
 scalar_t__ UART_TSH (struct uart_port*) ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  mvebu_uart_stop_tx (struct uart_port*) ; 
 unsigned int readl (scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mvebu_uart_tx_chars(struct uart_port *port, unsigned int status)
{
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int count;
	unsigned int st;

	if (port->x_char) {
		writel(port->x_char, port->membase + UART_TSH(port));
		port->icount.tx++;
		port->x_char = 0;
		return;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		mvebu_uart_stop_tx(port);
		return;
	}

	for (count = 0; count < port->fifosize; count++) {
		writel(xmit->buf[xmit->tail], port->membase + UART_TSH(port));
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;

		if (uart_circ_empty(xmit))
			break;

		st = readl(port->membase + UART_STAT);
		if (st & STAT_TX_FIFO_FUL)
			break;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		mvebu_uart_stop_tx(port);
}