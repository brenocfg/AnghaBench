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
 int /*<<< orphan*/  OWL_UART_CTL ; 
 int /*<<< orphan*/  OWL_UART_CTL_TXIE ; 
 int /*<<< orphan*/  OWL_UART_STAT ; 
 int /*<<< orphan*/  OWL_UART_STAT_TIP ; 
 int /*<<< orphan*/  owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_uart_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  owl_uart_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 

__attribute__((used)) static void owl_uart_start_tx(struct uart_port *port)
{
	u32 val;

	if (uart_tx_stopped(port)) {
		owl_uart_stop_tx(port);
		return;
	}

	val = owl_uart_read(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_TIP;
	owl_uart_write(port, val, OWL_UART_STAT);

	val = owl_uart_read(port, OWL_UART_CTL);
	val |= OWL_UART_CTL_TXIE;
	owl_uart_write(port, val, OWL_UART_CTL);
}