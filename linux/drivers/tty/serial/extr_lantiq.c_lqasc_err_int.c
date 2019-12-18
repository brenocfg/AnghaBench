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
struct uart_port {scalar_t__ membase; } ;
struct ltq_uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ASCWHBSTATE_CLRFE ; 
 int ASCWHBSTATE_CLRPE ; 
 int ASCWHBSTATE_CLRROE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LTQ_ASC_WHBSTATE ; 
 int /*<<< orphan*/  asc_update_bits (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t
lqasc_err_int(int irq, void *_port)
{
	unsigned long flags;
	struct uart_port *port = (struct uart_port *)_port;
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	/* clear any pending interrupts */
	asc_update_bits(0, ASCWHBSTATE_CLRPE | ASCWHBSTATE_CLRFE |
		ASCWHBSTATE_CLRROE, port->membase + LTQ_ASC_WHBSTATE);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	return IRQ_HANDLED;
}