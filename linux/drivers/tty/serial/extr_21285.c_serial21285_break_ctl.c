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
struct uart_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int* CSR_H_UBRLCR ; 
 unsigned int H_UBRLCR_BREAK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void serial21285_break_ctl(struct uart_port *port, int break_state)
{
	unsigned long flags;
	unsigned int h_lcr;

	spin_lock_irqsave(&port->lock, flags);
	h_lcr = *CSR_H_UBRLCR;
	if (break_state)
		h_lcr |= H_UBRLCR_BREAK;
	else
		h_lcr &= ~H_UBRLCR_BREAK;
	*CSR_H_UBRLCR = h_lcr;
	spin_unlock_irqrestore(&port->lock, flags);
}