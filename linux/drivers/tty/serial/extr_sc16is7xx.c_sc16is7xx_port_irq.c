#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  line; int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {TYPE_1__* p; } ;
struct TYPE_2__ {struct uart_port port; } ;

/* Variables and functions */
 unsigned int SC16IS7XX_IIR_ID_MASK ; 
 unsigned int SC16IS7XX_IIR_NO_INT_BIT ; 
#define  SC16IS7XX_IIR_RDI_SRC 132 
 int /*<<< orphan*/  SC16IS7XX_IIR_REG ; 
#define  SC16IS7XX_IIR_RLSE_SRC 131 
#define  SC16IS7XX_IIR_RTOI_SRC 130 
#define  SC16IS7XX_IIR_THRI_SRC 129 
#define  SC16IS7XX_IIR_XOFFI_SRC 128 
 int /*<<< orphan*/  SC16IS7XX_RXLVL_REG ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sc16is7xx_handle_rx (struct uart_port*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sc16is7xx_handle_tx (struct uart_port*) ; 
 unsigned int sc16is7xx_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sc16is7xx_port_irq(struct sc16is7xx_port *s, int portno)
{
	struct uart_port *port = &s->p[portno].port;

	do {
		unsigned int iir, rxlen;

		iir = sc16is7xx_port_read(port, SC16IS7XX_IIR_REG);
		if (iir & SC16IS7XX_IIR_NO_INT_BIT)
			return false;

		iir &= SC16IS7XX_IIR_ID_MASK;

		switch (iir) {
		case SC16IS7XX_IIR_RDI_SRC:
		case SC16IS7XX_IIR_RLSE_SRC:
		case SC16IS7XX_IIR_RTOI_SRC:
		case SC16IS7XX_IIR_XOFFI_SRC:
			rxlen = sc16is7xx_port_read(port, SC16IS7XX_RXLVL_REG);
			if (rxlen)
				sc16is7xx_handle_rx(port, rxlen, iir);
			break;
		case SC16IS7XX_IIR_THRI_SRC:
			sc16is7xx_handle_tx(port);
			break;
		default:
			dev_err_ratelimited(port->dev,
					    "ttySC%i: Unexpected interrupt: %x",
					    port->line, iir);
			break;
		}
	} while (0);
	return true;
}