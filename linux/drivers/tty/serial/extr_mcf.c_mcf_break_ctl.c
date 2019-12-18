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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MCFUART_UCR ; 
 int /*<<< orphan*/  MCFUART_UCR_CMDBREAKSTART ; 
 int /*<<< orphan*/  MCFUART_UCR_CMDBREAKSTOP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcf_break_ctl(struct uart_port *port, int break_state)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	if (break_state == -1)
		writeb(MCFUART_UCR_CMDBREAKSTART, port->membase + MCFUART_UCR);
	else
		writeb(MCFUART_UCR_CMDBREAKSTOP, port->membase + MCFUART_UCR);
	spin_unlock_irqrestore(&port->lock, flags);
}