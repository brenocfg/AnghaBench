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
typedef  unsigned short u16 ;
struct uart_port {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct sci_port {scalar_t__ chan_tx; int /*<<< orphan*/  work_tx; scalar_t__ cookie_tx; TYPE_2__ port; } ;
struct TYPE_3__ {int /*<<< orphan*/  xmit; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCSCR ; 
 unsigned short SCSCR_TDRQE ; 
 unsigned short SCSCR_TIE ; 
 scalar_t__ dma_submit_error (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 unsigned short serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,unsigned short) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 
 int /*<<< orphan*/  uart_circ_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sci_start_tx(struct uart_port *port)
{
	struct sci_port *s = to_sci_port(port);
	unsigned short ctrl;

#ifdef CONFIG_SERIAL_SH_SCI_DMA
	if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
		u16 new, scr = serial_port_in(port, SCSCR);
		if (s->chan_tx)
			new = scr | SCSCR_TDRQE;
		else
			new = scr & ~SCSCR_TDRQE;
		if (new != scr)
			serial_port_out(port, SCSCR, new);
	}

	if (s->chan_tx && !uart_circ_empty(&s->port.state->xmit) &&
	    dma_submit_error(s->cookie_tx)) {
		s->cookie_tx = 0;
		schedule_work(&s->work_tx);
	}
#endif

	if (!s->chan_tx || port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
		/* Set TIE (Transmit Interrupt Enable) bit in SCSCR */
		ctrl = serial_port_in(port, SCSCR);
		serial_port_out(port, SCSCR, ctrl | SCSCR_TIE);
	}
}