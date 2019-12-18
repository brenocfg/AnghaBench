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
struct uart_port {TYPE_3__ icount; scalar_t__ membase; TYPE_2__* state; } ;
struct stm32_usart_offsets {scalar_t__ tdr; scalar_t__ isr; int /*<<< orphan*/  cr3; } ;
struct stm32_port {int tx_dma_busy; TYPE_1__* info; } ;
struct circ_buf {size_t tail; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {struct circ_buf xmit; } ;
struct TYPE_4__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int UART_XMIT_SIZE ; 
 int /*<<< orphan*/  USART_CR3_DMAT ; 
 int USART_SR_TXE ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_tx_interrupt_disable (struct uart_port*) ; 
 int /*<<< orphan*/  stm32_tx_interrupt_enable (struct uart_port*) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_transmit_chars_pio(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	struct circ_buf *xmit = &port->state->xmit;

	if (stm32_port->tx_dma_busy) {
		stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		stm32_port->tx_dma_busy = false;
	}

	while (!uart_circ_empty(xmit)) {
		/* Check that TDR is empty before filling FIFO */
		if (!(readl_relaxed(port->membase + ofs->isr) & USART_SR_TXE))
			break;
		writel_relaxed(xmit->buf[xmit->tail], port->membase + ofs->tdr);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}

	/* rely on TXE irq (mask or unmask) for sending remaining data */
	if (uart_circ_empty(xmit))
		stm32_tx_interrupt_disable(port);
	else
		stm32_tx_interrupt_enable(port);
}