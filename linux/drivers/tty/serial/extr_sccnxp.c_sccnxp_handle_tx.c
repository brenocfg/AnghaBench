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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_3__ icount; scalar_t__ x_char; int /*<<< orphan*/  dev; TYPE_1__* state; } ;
struct sccnxp_port {TYPE_2__* chip; } ;
struct circ_buf {size_t tail; scalar_t__* buf; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_OP ; 
 int /*<<< orphan*/  IMR_TXRDY ; 
 int SCCNXP_HAVE_IO ; 
 int /*<<< orphan*/  SCCNXP_SR_REG ; 
 int /*<<< orphan*/  SCCNXP_THR_REG ; 
 int SR_TXEMT ; 
 int SR_TXRDY ; 
 int UART_XMIT_SIZE ; 
 scalar_t__ WAKEUP_CHARS ; 
 struct sccnxp_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_disable_irq (struct uart_port*,int /*<<< orphan*/ ) ; 
 int sccnxp_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sccnxp_port_write (struct uart_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sccnxp_set_bit (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 scalar_t__ unlikely (scalar_t__) ; 

__attribute__((used)) static void sccnxp_handle_tx(struct uart_port *port)
{
	u8 sr;
	struct circ_buf *xmit = &port->state->xmit;
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	if (unlikely(port->x_char)) {
		sccnxp_port_write(port, SCCNXP_THR_REG, port->x_char);
		port->icount.tx++;
		port->x_char = 0;
		return;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		/* Disable TX if FIFO is empty */
		if (sccnxp_port_read(port, SCCNXP_SR_REG) & SR_TXEMT) {
			sccnxp_disable_irq(port, IMR_TXRDY);

			/* Set direction to input */
			if (s->chip->flags & SCCNXP_HAVE_IO)
				sccnxp_set_bit(port, DIR_OP, 0);
		}
		return;
	}

	while (!uart_circ_empty(xmit)) {
		sr = sccnxp_port_read(port, SCCNXP_SR_REG);
		if (!(sr & SR_TXRDY))
			break;

		sccnxp_port_write(port, SCCNXP_THR_REG, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);
}