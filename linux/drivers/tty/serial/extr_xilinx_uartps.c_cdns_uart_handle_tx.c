#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;
struct uart_port {unsigned int fifosize; TYPE_2__* state; TYPE_1__ icount; scalar_t__ membase; } ;
struct TYPE_7__ {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {TYPE_3__ xmit; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_FIFO ; 
 scalar_t__ CDNS_UART_IDR ; 
 int /*<<< orphan*/  CDNS_UART_IXR_TXEMPTY ; 
 scalar_t__ CDNS_UART_SR ; 
 int CDNS_UART_SR_TXFULL ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int readl (scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (TYPE_3__*) ; 
 scalar_t__ uart_circ_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cdns_uart_handle_tx(void *dev_id)
{
	struct uart_port *port = (struct uart_port *)dev_id;
	unsigned int numbytes;

	if (uart_circ_empty(&port->state->xmit)) {
		writel(CDNS_UART_IXR_TXEMPTY, port->membase + CDNS_UART_IDR);
	} else {
		numbytes = port->fifosize;
		while (numbytes && !uart_circ_empty(&port->state->xmit) &&
		       !(readl(port->membase + CDNS_UART_SR) &
						CDNS_UART_SR_TXFULL)) {
			/*
			 * Get the data from the UART circular buffer
			 * and write it to the cdns_uart's TX_FIFO
			 * register.
			 */
			writel(
				port->state->xmit.buf[port->state->xmit.tail],
					port->membase + CDNS_UART_FIFO);

			port->icount.tx++;

			/*
			 * Adjust the tail of the UART buffer and wrap
			 * the buffer if it reaches limit.
			 */
			port->state->xmit.tail =
				(port->state->xmit.tail + 1) &
					(UART_XMIT_SIZE - 1);

			numbytes--;
		}

		if (uart_circ_chars_pending(
				&port->state->xmit) < WAKEUP_CHARS)
			uart_write_wakeup(port);
	}
}