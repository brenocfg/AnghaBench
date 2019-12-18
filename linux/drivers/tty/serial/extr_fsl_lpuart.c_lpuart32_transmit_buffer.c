#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tx; } ;
struct TYPE_10__ {TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct lpuart_port {unsigned long txfifo_size; TYPE_3__ port; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_8__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTDATA ; 
 int /*<<< orphan*/  UARTWATER ; 
 unsigned long UARTWATER_COUNT_MASK ; 
 unsigned long UARTWATER_TXCNT_OFF ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 unsigned long lpuart32_read (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_stop_tx (TYPE_3__*) ; 
 int /*<<< orphan*/  lpuart32_write (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lpuart_stopped_or_empty (TYPE_3__*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_3__*) ; 

__attribute__((used)) static inline void lpuart32_transmit_buffer(struct lpuart_port *sport)
{
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned long txcnt;

	if (sport->port.x_char) {
		lpuart32_write(&sport->port, sport->port.x_char, UARTDATA);
		sport->port.icount.tx++;
		sport->port.x_char = 0;
		return;
	}

	if (lpuart_stopped_or_empty(&sport->port)) {
		lpuart32_stop_tx(&sport->port);
		return;
	}

	txcnt = lpuart32_read(&sport->port, UARTWATER);
	txcnt = txcnt >> UARTWATER_TXCNT_OFF;
	txcnt &= UARTWATER_COUNT_MASK;
	while (!uart_circ_empty(xmit) && (txcnt < sport->txfifo_size)) {
		lpuart32_write(&sport->port, xmit->buf[xmit->tail], UARTDATA);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
		txcnt = lpuart32_read(&sport->port, UARTWATER);
		txcnt = txcnt >> UARTWATER_TXCNT_OFF;
		txcnt &= UARTWATER_COUNT_MASK;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

	if (uart_circ_empty(xmit))
		lpuart32_stop_tx(&sport->port);
}