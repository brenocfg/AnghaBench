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
struct uart_port {int fifosize; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; scalar_t__ membase; } ;

/* Variables and functions */
 int AML_UART_CLEAR_ERR ; 
 scalar_t__ AML_UART_CONTROL ; 
 scalar_t__ AML_UART_MISC ; 
 int AML_UART_RECV_IRQ (int) ; 
 int AML_UART_RX_EN ; 
 int AML_UART_RX_INT_EN ; 
 int AML_UART_TX_EN ; 
 int AML_UART_TX_INT_EN ; 
 int AML_UART_XMIT_IRQ (int) ; 
 int /*<<< orphan*/  meson_uart_interrupt ; 
 int readl (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int meson_uart_startup(struct uart_port *port)
{
	u32 val;
	int ret = 0;

	val = readl(port->membase + AML_UART_CONTROL);
	val |= AML_UART_CLEAR_ERR;
	writel(val, port->membase + AML_UART_CONTROL);
	val &= ~AML_UART_CLEAR_ERR;
	writel(val, port->membase + AML_UART_CONTROL);

	val |= (AML_UART_RX_EN | AML_UART_TX_EN);
	writel(val, port->membase + AML_UART_CONTROL);

	val |= (AML_UART_RX_INT_EN | AML_UART_TX_INT_EN);
	writel(val, port->membase + AML_UART_CONTROL);

	val = (AML_UART_RECV_IRQ(1) | AML_UART_XMIT_IRQ(port->fifosize / 2));
	writel(val, port->membase + AML_UART_MISC);

	ret = request_irq(port->irq, meson_uart_interrupt, 0,
			  port->name, port);

	return ret;
}