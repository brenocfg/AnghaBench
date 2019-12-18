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
struct uart_port {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_CONTROL_REG ; 
 int /*<<< orphan*/  ALTERA_UART_STATUS_REG ; 
 int /*<<< orphan*/  PORT_ALTERA_UART ; 
 int /*<<< orphan*/  altera_uart_writel (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void altera_uart_config_port(struct uart_port *port, int flags)
{
	port->type = PORT_ALTERA_UART;

	/* Clear mask, so no surprise interrupts. */
	altera_uart_writel(port, 0, ALTERA_UART_CONTROL_REG);
	/* Clear status register */
	altera_uart_writel(port, 0, ALTERA_UART_STATUS_REG);
}