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
struct uart_port {int dummy; } ;
struct stm32_usart_offsets {int /*<<< orphan*/  cr3; } ;
struct stm32_port {int tx_dma_busy; TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  USART_CR3_DMAT ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_transmit_chars (struct uart_port*) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static void stm32_tx_dma_complete(void *arg)
{
	struct uart_port *port = arg;
	struct stm32_port *stm32port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32port->info->ofs;

	stm32_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
	stm32port->tx_dma_busy = false;

	/* Let's see if we have pending data to send */
	stm32_transmit_chars(port);
}