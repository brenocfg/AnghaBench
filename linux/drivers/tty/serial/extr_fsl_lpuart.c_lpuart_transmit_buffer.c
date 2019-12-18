#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tx; } ;
struct TYPE_8__ {TYPE_2__ icount; scalar_t__ membase; scalar_t__ x_char; TYPE_1__* state; } ;
struct lpuart_port {scalar_t__ txfifo_size; TYPE_3__ port; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_6__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ UARTDR ; 
 scalar_t__ UARTTCFIFO ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  lpuart_stop_tx (TYPE_3__*) ; 
 scalar_t__ lpuart_stopped_or_empty (TYPE_3__*) ; 
 scalar_t__ readb (scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void lpuart_transmit_buffer(struct lpuart_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;

	if (sport->port.x_char) {
		writeb(sport->port.x_char, sport->port.membase + UARTDR);
		sport->port.icount.tx++;
		sport->port.x_char = 0;
		return;
	}

	if (lpuart_stopped_or_empty(&sport->port)) {
		lpuart_stop_tx(&sport->port);
		return;
	}

	while (!uart_circ_empty(xmit) &&
		(readb(sport->port.membase + UARTTCFIFO) < sport->txfifo_size)) {
		writeb(xmit->buf[xmit->tail], sport->port.membase + UARTDR);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (uart_circ_empty(xmit))
		lpuart_stop_tx(&sport->port);
}