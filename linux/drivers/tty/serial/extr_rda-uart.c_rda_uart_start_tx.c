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
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDA_UART_IRQ_MASK ; 
 int /*<<< orphan*/  RDA_UART_TX_DATA_NEEDED ; 
 int /*<<< orphan*/  rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rda_uart_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  rda_uart_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 

__attribute__((used)) static void rda_uart_start_tx(struct uart_port *port)
{
	u32 val;

	if (uart_tx_stopped(port)) {
		rda_uart_stop_tx(port);
		return;
	}

	val = rda_uart_read(port, RDA_UART_IRQ_MASK);
	val |= RDA_UART_TX_DATA_NEEDED;
	rda_uart_write(port, val, RDA_UART_IRQ_MASK);
}