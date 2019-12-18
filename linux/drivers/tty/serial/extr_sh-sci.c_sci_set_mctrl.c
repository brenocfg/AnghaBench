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
struct sci_port {scalar_t__ autorts; int /*<<< orphan*/  has_rtscts; int /*<<< orphan*/  gpios; } ;
struct plat_sci_reg {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCFCR ; 
 int SCFCR_LOOP ; 
 int SCFCR_MCE ; 
 int /*<<< orphan*/  SCPCR ; 
 int SCPCR_RTSC ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  mctrl_gpio_set (int /*<<< orphan*/ ,unsigned int) ; 
 struct plat_sci_reg* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_set_rts (struct uart_port*,int) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct sci_port *s = to_sci_port(port);

	if (mctrl & TIOCM_LOOP) {
		const struct plat_sci_reg *reg;

		/*
		 * Standard loopback mode for SCFCR ports.
		 */
		reg = sci_getreg(port, SCFCR);
		if (reg->size)
			serial_port_out(port, SCFCR,
					serial_port_in(port, SCFCR) |
					SCFCR_LOOP);
	}

	mctrl_gpio_set(s->gpios, mctrl);

	if (!s->has_rtscts)
		return;

	if (!(mctrl & TIOCM_RTS)) {
		/* Disable Auto RTS */
		serial_port_out(port, SCFCR,
				serial_port_in(port, SCFCR) & ~SCFCR_MCE);

		/* Clear RTS */
		sci_set_rts(port, 0);
	} else if (s->autorts) {
		if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
			/* Enable RTS# pin function */
			serial_port_out(port, SCPCR,
				serial_port_in(port, SCPCR) & ~SCPCR_RTSC);
		}

		/* Enable Auto RTS */
		serial_port_out(port, SCFCR,
				serial_port_in(port, SCFCR) | SCFCR_MCE);
	} else {
		/* Set RTS */
		sci_set_rts(port, 1);
	}
}