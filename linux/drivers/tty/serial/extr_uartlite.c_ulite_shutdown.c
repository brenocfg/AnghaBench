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
struct uartlite_data {int /*<<< orphan*/  clk; } ;
struct uart_port {int /*<<< orphan*/  irq; struct uartlite_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULITE_CONTROL ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  uart_in32 (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  uart_out32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 

__attribute__((used)) static void ulite_shutdown(struct uart_port *port)
{
	struct uartlite_data *pdata = port->private_data;

	uart_out32(0, ULITE_CONTROL, port);
	uart_in32(ULITE_CONTROL, port); /* dummy */
	free_irq(port->irq, port);
	clk_disable(pdata->clk);
}