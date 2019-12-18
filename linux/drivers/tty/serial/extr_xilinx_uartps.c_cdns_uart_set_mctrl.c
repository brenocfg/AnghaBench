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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; struct cdns_uart* private_data; } ;
struct cdns_uart {scalar_t__ cts_override; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_MODEMCR ; 
 int CDNS_UART_MODEMCR_DTR ; 
 int CDNS_UART_MODEMCR_FCM ; 
 int CDNS_UART_MODEMCR_RTS ; 
 scalar_t__ CDNS_UART_MR ; 
 int CDNS_UART_MR_CHMODE_L_LOOP ; 
 int CDNS_UART_MR_CHMODE_MASK ; 
 int CDNS_UART_MR_CHMODE_NORM ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cdns_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	u32 val;
	u32 mode_reg;
	struct cdns_uart *cdns_uart_data = port->private_data;

	if (cdns_uart_data->cts_override)
		return;

	val = readl(port->membase + CDNS_UART_MODEMCR);
	mode_reg = readl(port->membase + CDNS_UART_MR);

	val &= ~(CDNS_UART_MODEMCR_RTS | CDNS_UART_MODEMCR_DTR |
		 CDNS_UART_MODEMCR_FCM);
	mode_reg &= ~CDNS_UART_MR_CHMODE_MASK;

	if (mctrl & TIOCM_RTS || mctrl & TIOCM_DTR)
		val |= CDNS_UART_MODEMCR_FCM;
	if (mctrl & TIOCM_LOOP)
		mode_reg |= CDNS_UART_MR_CHMODE_L_LOOP;
	else
		mode_reg |= CDNS_UART_MR_CHMODE_NORM;

	writel(val, port->membase + CDNS_UART_MODEMCR);
	writel(mode_reg, port->membase + CDNS_UART_MR);
}