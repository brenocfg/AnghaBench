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
struct uart_port {scalar_t__ membase; } ;
struct stm32_usart_offsets {scalar_t__ isr; } ;
struct stm32_port {TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 unsigned int USART_SR_TXE ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static unsigned int stm32_tx_empty(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;

	return readl_relaxed(port->membase + ofs->isr) & USART_SR_TXE;
}