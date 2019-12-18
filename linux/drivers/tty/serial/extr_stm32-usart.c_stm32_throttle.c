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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct stm32_usart_offsets {int /*<<< orphan*/  cr3; int /*<<< orphan*/  cr1; } ;
struct stm32_port {scalar_t__ cr3_irq; scalar_t__ cr1_irq; TYPE_1__* info; } ;
struct TYPE_2__ {struct stm32_usart_offsets ofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stm32_clr_bits (struct uart_port*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct stm32_port* to_stm32_port (struct uart_port*) ; 

__attribute__((used)) static void stm32_throttle(struct uart_port *port)
{
	struct stm32_port *stm32_port = to_stm32_port(port);
	struct stm32_usart_offsets *ofs = &stm32_port->info->ofs;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	stm32_clr_bits(port, ofs->cr1, stm32_port->cr1_irq);
	if (stm32_port->cr3_irq)
		stm32_clr_bits(port, ofs->cr3, stm32_port->cr3_irq);

	spin_unlock_irqrestore(&port->lock, flags);
}