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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct atmel_uart_port {unsigned int tx_done_mask; int hd_start_rx; int /*<<< orphan*/  tasklet_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_US_CSR ; 
 int /*<<< orphan*/  ATMEL_US_IDR ; 
 int ATMEL_US_TXEMPTY ; 
 int /*<<< orphan*/  atmel_start_rx (struct uart_port*) ; 
 int /*<<< orphan*/  atmel_tasklet_schedule (struct atmel_uart_port*,int /*<<< orphan*/ *) ; 
 int atmel_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_uart_writel (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
atmel_handle_transmit(struct uart_port *port, unsigned int pending)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (pending & atmel_port->tx_done_mask) {
		atmel_uart_writel(port, ATMEL_US_IDR,
				  atmel_port->tx_done_mask);

		/* Start RX if flag was set and FIFO is empty */
		if (atmel_port->hd_start_rx) {
			if (!(atmel_uart_readl(port, ATMEL_US_CSR)
					& ATMEL_US_TXEMPTY))
				dev_warn(port->dev, "Should start RX, but TX fifo is not empty\n");

			atmel_port->hd_start_rx = false;
			atmel_start_rx(port);
		}

		atmel_tasklet_schedule(atmel_port, &atmel_port->tasklet_tx);
	}
}