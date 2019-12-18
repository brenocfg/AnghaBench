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
struct uart_port {int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpm_uart_tx_pump (struct uart_port*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpm_uart_int_tx(struct uart_port *port)
{
	pr_debug("CPM uart[%d]:TX INT\n", port->line);

	cpm_uart_tx_pump(port);
}