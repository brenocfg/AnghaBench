#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct uart_port {TYPE_3__ icount; scalar_t__ x_char; scalar_t__ membase; TYPE_2__* state; } ;
struct stm32_usart_offsets {scalar_t__ cr3; scalar_t__ icr; scalar_t__ isr; scalar_t__ tdr; } ;
struct stm32_port {scalar_t__ tx_ch; scalar_t__ tx_dma_busy; TYPE_1__* info; } ;
struct circ_buf {int dummy; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;
struct TYPE_4__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 scalar_t__ UNDEF_REG ; 
 int /*<<< orphan*/  USART_CR3_DMAT ; 
 int /*<<< orphan*/  USART_ICR_TCCF ; 
 int /*<<< orphan*/  USART_SR_TC ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_set_bits (struct uart_port*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_transmit_chars_dma (struct uart_port*) ; 
 int /*<<< orphan*/  stm32_transmit_chars_pio (struct uart_port*) ; 
 int /*<<< orphan*/  stm32_tx_interrupt_disable (struct uart_port*) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void stm32_transmit_chars(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct circ_buf *xmit = &port->state->xmit;

	if (port->x_char) {
		if (stm32_port->tx_dma_busy)
			stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		writel_relaxed(port->x_char, port->membase + ofs->tdr);
		port->x_char = 0;
		port->icount.tx++;
		if (stm32_port->tx_dma_busy)
			stm32_set_bits(port, ofs->cr3, USART_CR3_DMAT);
		return;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
		stm32_tx_interrupt_disable(port);
		return;
	}

	if (ofs->icr == UNDEF_REG)
		stm32_clr_bits(port, ofs->isr, USART_SR_TC);
	else
		stm32_set_bits(port, ofs->icr, USART_ICR_TCCF);

	if (stm32_port->tx_ch)
		stm32_transmit_chars_dma(port);
	else
		stm32_transmit_chars_pio(port);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		stm32_tx_interrupt_disable(port);
}