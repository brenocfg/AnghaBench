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
struct uart_port {int uartclk; } ;

/* Variables and functions */
 unsigned int MAX310X_BRGCFG_2XMODE_BIT ; 
 unsigned int MAX310X_BRGCFG_4XMODE_BIT ; 
 int /*<<< orphan*/  MAX310X_BRGCFG_REG ; 
 int /*<<< orphan*/  MAX310X_BRGDIVLSB_REG ; 
 int /*<<< orphan*/  MAX310X_BRGDIVMSB_REG ; 
 int /*<<< orphan*/  max310x_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max310x_set_baud(struct uart_port *port, int baud)
{
	unsigned int mode = 0, div = 0, frac = 0, c = 0, F = 0;

	/*
	 * Calculate the integer divisor first. Select a proper mode
	 * in case if the requested baud is too high for the pre-defined
	 * clocks frequency.
	 */
	div = port->uartclk / baud;
	if (div < 8) {
		/* Mode x4 */
		c = 4;
		mode = MAX310X_BRGCFG_4XMODE_BIT;
	} else if (div < 16) {
		/* Mode x2 */
		c = 8;
		mode = MAX310X_BRGCFG_2XMODE_BIT;
	} else {
		c = 16;
	}

	/* Calculate the divisor in accordance with the fraction coefficient */
	div /= c;
	F = c*baud;

	/* Calculate the baud rate fraction */
	if (div > 0)
		frac = (16*(port->uartclk % F)) / F;
	else
		div = 1;

	max310x_port_write(port, MAX310X_BRGDIVMSB_REG, div >> 8);
	max310x_port_write(port, MAX310X_BRGDIVLSB_REG, div);
	max310x_port_write(port, MAX310X_BRGCFG_REG, frac | mode);

	/* Return the actual baud rate we just programmed */
	return (16*port->uartclk) / (c*(16*div + frac));
}