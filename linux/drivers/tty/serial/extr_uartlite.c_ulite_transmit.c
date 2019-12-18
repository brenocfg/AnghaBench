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
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_1__ icount; scalar_t__ x_char; TYPE_2__* state; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 int ULITE_STATUS_TXFULL ; 
 int /*<<< orphan*/  ULITE_TX ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_out32 (scalar_t__,int /*<<< orphan*/ ,struct uart_port*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 

__attribute__((used)) static int ulite_transmit(struct uart_port *port, int stat)
{
	struct circ_buf *xmit  = &port->state->xmit;

	if (stat & ULITE_STATUS_TXFULL)
		return 0;

	if (port->x_char) {
		uart_out32(port->x_char, ULITE_TX, port);
		port->x_char = 0;
		port->icount.tx++;
		return 1;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port))
		return 0;

	uart_out32(xmit->buf[xmit->tail], ULITE_TX, port);
	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE-1);
	port->icount.tx++;

	/* wake up */
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	return 1;
}