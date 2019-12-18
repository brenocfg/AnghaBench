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
struct uart_port {unsigned int x_char; unsigned int fifosize; TYPE_2__ icount; TYPE_1__* state; } ;
struct circ_buf {unsigned int* buf; size_t tail; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_FIFO_REG ; 
 int /*<<< orphan*/  UART_IR_REG ; 
 int /*<<< orphan*/  UART_MCTL_REG ; 
 unsigned int UART_MCTL_TXFIFOFILL_MASK ; 
 unsigned int UART_MCTL_TXFIFOFILL_SHIFT ; 
 unsigned int UART_TX_INT_MASK ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static void bcm_uart_do_tx(struct uart_port *port)
{
	struct circ_buf *xmit;
	unsigned int val, max_count;

	if (port->x_char) {
		bcm_uart_writel(port, port->x_char, UART_FIFO_REG);
		port->icount.tx++;
		port->x_char = 0;
		return;
	}

	if (uart_tx_stopped(port)) {
		bcm_uart_stop_tx(port);
		return;
	}

	xmit = &port->state->xmit;
	if (uart_circ_empty(xmit))
		goto txq_empty;

	val = bcm_uart_readl(port, UART_MCTL_REG);
	val = (val & UART_MCTL_TXFIFOFILL_MASK) >> UART_MCTL_TXFIFOFILL_SHIFT;
	max_count = port->fifosize - val;

	while (max_count--) {
		unsigned int c;

		c = xmit->buf[xmit->tail];
		bcm_uart_writel(port, c, UART_FIFO_REG);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		if (uart_circ_empty(xmit))
			break;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		goto txq_empty;
	return;

txq_empty:
	/* nothing to send, disable transmit interrupt */
	val = bcm_uart_readl(port, UART_IR_REG);
	val &= ~UART_TX_INT_MASK;
	bcm_uart_writel(port, val, UART_IR_REG);
	return;
}