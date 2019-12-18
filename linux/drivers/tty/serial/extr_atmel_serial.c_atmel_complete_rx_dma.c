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
struct uart_port {int dummy; } ;
struct atmel_uart_port {int /*<<< orphan*/  tasklet_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_tasklet_schedule (struct atmel_uart_port*,int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void atmel_complete_rx_dma(void *arg)
{
	struct uart_port *port = arg;
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	atmel_tasklet_schedule(atmel_port, &atmel_port->tasklet_rx);
}