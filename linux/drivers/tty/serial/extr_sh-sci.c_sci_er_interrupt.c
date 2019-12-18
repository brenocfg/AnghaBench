#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_port {scalar_t__ type; } ;
struct sci_port {scalar_t__* irqs; int /*<<< orphan*/  chan_tx; int /*<<< orphan*/  chan_rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PORT_SCI ; 
 size_t SCIx_BRI_IRQ ; 
 size_t SCIx_ERI_IRQ ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_BRK (struct uart_port*) ; 
 unsigned short SCxSR_ERRORS (struct uart_port*) ; 
 int /*<<< orphan*/  SCxSR_ERROR_CLEAR (struct uart_port*) ; 
 int /*<<< orphan*/  SCxSR_RDxF_CLEAR (struct uart_port*) ; 
 int /*<<< orphan*/  sci_br_interrupt (int,void*) ; 
 int /*<<< orphan*/  sci_clear_SCxSR (struct uart_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_handle_errors (struct uart_port*) ; 
 int /*<<< orphan*/  sci_handle_fifo_overrun (struct uart_port*) ; 
 int /*<<< orphan*/  sci_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  sci_tx_interrupt (int,void*) ; 
 unsigned short serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t sci_er_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct sci_port *s = to_sci_port(port);

	if (s->irqs[SCIx_ERI_IRQ] == s->irqs[SCIx_BRI_IRQ]) {
		/* Break and Error interrupts are muxed */
		unsigned short ssr_status = serial_port_in(port, SCxSR);

		/* Break Interrupt */
		if (ssr_status & SCxSR_BRK(port))
			sci_br_interrupt(irq, ptr);

		/* Break only? */
		if (!(ssr_status & SCxSR_ERRORS(port)))
			return IRQ_HANDLED;
	}

	/* Handle errors */
	if (port->type == PORT_SCI) {
		if (sci_handle_errors(port)) {
			/* discard character in rx buffer */
			serial_port_in(port, SCxSR);
			sci_clear_SCxSR(port, SCxSR_RDxF_CLEAR(port));
		}
	} else {
		sci_handle_fifo_overrun(port);
		if (!s->chan_rx)
			sci_receive_chars(port);
	}

	sci_clear_SCxSR(port, SCxSR_ERROR_CLEAR(port));

	/* Kick the transmission */
	if (!s->chan_tx)
		sci_tx_interrupt(irq, ptr);

	return IRQ_HANDLED;
}