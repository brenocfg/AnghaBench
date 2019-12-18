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
typedef  int u16 ;
struct uart_port {scalar_t__ type; int /*<<< orphan*/  dev; } ;
struct sci_port {int rx_trigger; int rx_fifo_timeout; int rx_frame; int /*<<< orphan*/  rx_fifo_timer; int /*<<< orphan*/  rx_timeout; int /*<<< orphan*/  rx_timer; scalar_t__ chan_rx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int SCIF_DR ; 
 int /*<<< orphan*/  SCSCR ; 
 int SCSCR_RDRQE ; 
 int SCSCR_RIE ; 
 int /*<<< orphan*/  SCxSR ; 
 int SCxSR_RDxF (struct uart_port*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sci_dma_rx_submit (struct sci_port*,int) ; 
 int /*<<< orphan*/  sci_receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  scif_rtrg_enabled (struct uart_port*) ; 
 int /*<<< orphan*/  scif_set_rtrg (struct uart_port*,int) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_hrtimer_us (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t sci_rx_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct sci_port *s = to_sci_port(port);

#ifdef CONFIG_SERIAL_SH_SCI_DMA
	if (s->chan_rx) {
		u16 scr = serial_port_in(port, SCSCR);
		u16 ssr = serial_port_in(port, SCxSR);

		/* Disable future Rx interrupts */
		if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
			disable_irq_nosync(irq);
			scr |= SCSCR_RDRQE;
		} else {
			if (sci_dma_rx_submit(s, false) < 0)
				goto handle_pio;

			scr &= ~SCSCR_RIE;
		}
		serial_port_out(port, SCSCR, scr);
		/* Clear current interrupt */
		serial_port_out(port, SCxSR,
				ssr & ~(SCIF_DR | SCxSR_RDxF(port)));
		dev_dbg(port->dev, "Rx IRQ %lu: setup t-out in %u us\n",
			jiffies, s->rx_timeout);
		start_hrtimer_us(&s->rx_timer, s->rx_timeout);

		return IRQ_HANDLED;
	}

handle_pio:
#endif

	if (s->rx_trigger > 1 && s->rx_fifo_timeout > 0) {
		if (!scif_rtrg_enabled(port))
			scif_set_rtrg(port, s->rx_trigger);

		mod_timer(&s->rx_fifo_timer, jiffies + DIV_ROUND_UP(
			  s->rx_frame * HZ * s->rx_fifo_timeout, 1000000));
	}

	/* I think sci_receive_chars has to be called irrespective
	 * of whether the I_IXOFF is set, otherwise, how is the interrupt
	 * to be disabled?
	 */
	sci_receive_chars(port);

	return IRQ_HANDLED;
}