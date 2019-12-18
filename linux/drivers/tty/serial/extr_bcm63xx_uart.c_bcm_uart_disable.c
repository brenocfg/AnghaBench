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
 unsigned int UART_CTL_BRGEN_MASK ; 
 int /*<<< orphan*/  UART_CTL_REG ; 
 unsigned int UART_CTL_RXEN_MASK ; 
 unsigned int UART_CTL_TXEN_MASK ; 
 unsigned int bcm_uart_readl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_uart_writel (struct uart_port*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_uart_disable(struct uart_port *port)
{
	unsigned int val;

	val = bcm_uart_readl(port, UART_CTL_REG);
	val &= ~(UART_CTL_BRGEN_MASK | UART_CTL_TXEN_MASK |
		 UART_CTL_RXEN_MASK);
	bcm_uart_writel(port, val, UART_CTL_REG);
}