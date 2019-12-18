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
struct TYPE_4__ {scalar_t__ tx; } ;
struct uart_port {TYPE_2__ icount; int /*<<< orphan*/  dev; scalar_t__ x_char; TYPE_1__* state; } ;
struct sc16is7xx_port {int /*<<< orphan*/ * buf; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {struct circ_buf xmit; } ;

/* Variables and functions */
 unsigned int SC16IS7XX_FIFO_SIZE ; 
 int /*<<< orphan*/  SC16IS7XX_THR_REG ; 
 int /*<<< orphan*/  SC16IS7XX_TXLVL_REG ; 
 int UART_XMIT_SIZE ; 
 unsigned int WAKEUP_CHARS ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  sc16is7xx_fifo_write (struct uart_port*,unsigned int) ; 
 unsigned int sc16is7xx_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_port_write (struct uart_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static void sc16is7xx_handle_tx(struct uart_port *port)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int txlen, to_send, i;

	if (unlikely(port->x_char)) {
		sc16is7xx_port_write(port, SC16IS7XX_THR_REG, port->x_char);
		port->icount.tx++;
		port->x_char = 0;
		return;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port))
		return;

	/* Get length of data pending in circular buffer */
	to_send = uart_circ_chars_pending(xmit);
	if (likely(to_send)) {
		/* Limit to size of TX FIFO */
		txlen = sc16is7xx_port_read(port, SC16IS7XX_TXLVL_REG);
		if (txlen > SC16IS7XX_FIFO_SIZE) {
			dev_err_ratelimited(port->dev,
				"chip reports %d free bytes in TX fifo, but it only has %d",
				txlen, SC16IS7XX_FIFO_SIZE);
			txlen = 0;
		}
		to_send = (to_send > txlen) ? txlen : to_send;

		/* Add data to send */
		port->icount.tx += to_send;

		/* Convert to linear buffer */
		for (i = 0; i < to_send; ++i) {
			s->buf[i] = xmit->buf[xmit->tail];
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		}

		sc16is7xx_fifo_write(port, to_send);
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}