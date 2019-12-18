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

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_UART_STATUS_REG ; 
 int ALTERA_UART_STATUS_TMT_MSK ; 
 unsigned int TIOCSER_TEMT ; 
 int altera_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int altera_uart_tx_empty(struct uart_port *port)
{
	return (altera_uart_readl(port, ALTERA_UART_STATUS_REG) &
		ALTERA_UART_STATUS_TMT_MSK) ? TIOCSER_TEMT : 0;
}