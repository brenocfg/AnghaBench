#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx; } ;
struct uart_port {scalar_t__ membase; TYPE_3__ rs485; TYPE_2__ icount; scalar_t__ x_char; TYPE_1__* state; } ;
struct mcf_uart {scalar_t__ imr; struct uart_port port; } ;
struct circ_buf {size_t head; size_t tail; scalar_t__* buf; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ MCFUART_UCR ; 
 scalar_t__ MCFUART_UCR_TXDISABLE ; 
 scalar_t__ MCFUART_UIMR ; 
 scalar_t__ MCFUART_UIR_TXREADY ; 
 scalar_t__ MCFUART_USR ; 
 int MCFUART_USR_TXREADY ; 
 scalar_t__ MCFUART_UTB ; 
 int SER_RS485_ENABLED ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 int readb (scalar_t__) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mcf_tx_chars(struct mcf_uart *pp)
{
	struct uart_port *port = &pp->port;
	struct circ_buf *xmit = &port->state->xmit;

	if (port->x_char) {
		/* Send special char - probably flow control */
		writeb(port->x_char, port->membase + MCFUART_UTB);
		port->x_char = 0;
		port->icount.tx++;
		return;
	}

	while (readb(port->membase + MCFUART_USR) & MCFUART_USR_TXREADY) {
		if (xmit->head == xmit->tail)
			break;
		writeb(xmit->buf[xmit->tail], port->membase + MCFUART_UTB);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE -1);
		port->icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (xmit->head == xmit->tail) {
		pp->imr &= ~MCFUART_UIR_TXREADY;
		writeb(pp->imr, port->membase + MCFUART_UIMR);
		/* Disable TX to negate RTS automatically */
		if (port->rs485.flags & SER_RS485_ENABLED)
			writeb(MCFUART_UCR_TXDISABLE,
				port->membase + MCFUART_UCR);
	}
}