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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  uartclk; struct cdns_uart* private_data; } ;
struct cdns_uart {unsigned int baud; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_BAUDDIV ; 
 scalar_t__ CDNS_UART_BAUDGEN ; 
 scalar_t__ CDNS_UART_MR ; 
 int /*<<< orphan*/  CDNS_UART_MR_CLKSEL ; 
 unsigned int cdns_uart_calc_baud_divs (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned int cdns_uart_set_baud_rate(struct uart_port *port,
		unsigned int baud)
{
	unsigned int calc_baud;
	u32 cd = 0, bdiv = 0;
	u32 mreg;
	int div8;
	struct cdns_uart *cdns_uart = port->private_data;

	calc_baud = cdns_uart_calc_baud_divs(port->uartclk, baud, &bdiv, &cd,
			&div8);

	/* Write new divisors to hardware */
	mreg = readl(port->membase + CDNS_UART_MR);
	if (div8)
		mreg |= CDNS_UART_MR_CLKSEL;
	else
		mreg &= ~CDNS_UART_MR_CLKSEL;
	writel(mreg, port->membase + CDNS_UART_MR);
	writel(cd, port->membase + CDNS_UART_BAUDGEN);
	writel(bdiv, port->membase + CDNS_UART_BAUDDIV);
	cdns_uart->baud = baud;

	return calc_baud;
}