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
struct stm32_usart_offsets {int /*<<< orphan*/  cr1; int /*<<< orphan*/  cr3; } ;
struct stm32_port {scalar_t__ fifoen; TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  USART_CR1_TXEIE ; 
 int /*<<< orphan*/  USART_CR3_TXFTIE ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static void stm32_tx_interrupt_disable(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;

	if (stm32_port->fifoen)
		stm32_clr_bits(port, ofs->cr3, USART_CR3_TXFTIE);
	else
		stm32_clr_bits(port, ofs->cr1, USART_CR1_TXEIE);
}