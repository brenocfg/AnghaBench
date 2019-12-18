#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  lock; } ;
struct stm32_usart_offsets {scalar_t__ isr; scalar_t__ icr; } ;
struct stm32_port {scalar_t__ rx_ch; int /*<<< orphan*/  tx_ch; TYPE_1__* info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ UNDEF_REG ; 
 int /*<<< orphan*/  USART_ICR_RTOCF ; 
 int /*<<< orphan*/  USART_ICR_WUCF ; 
 int USART_SR_RTOF ; 
 int USART_SR_RXNE ; 
 int USART_SR_TXE ; 
 int USART_SR_WUF ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_receive_chars (struct uart_port*,int) ; 
 int /*<<< orphan*/  stm32_transmit_chars (struct uart_port*) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm32_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	u32 sr;

	spin_lock(&port->lock);

	sr = readl_relaxed(port->membase + ofs->isr);

	if ((sr & USART_SR_RTOF) && ofs->icr != UNDEF_REG)
		writel_relaxed(USART_ICR_RTOCF,
			       port->membase + ofs->icr);

	if ((sr & USART_SR_WUF) && (ofs->icr != UNDEF_REG))
		writel_relaxed(USART_ICR_WUCF,
			       port->membase + ofs->icr);

	if ((sr & USART_SR_RXNE) && !(stm32_port->rx_ch))
		stm32_receive_chars(port, false);

	if ((sr & USART_SR_TXE) && !(stm32_port->tx_ch))
		stm32_transmit_chars(port);

	spin_unlock(&port->lock);

	if (stm32_port->rx_ch)
		return IRQ_WAKE_THREAD;
	else
		return IRQ_HANDLED;
}