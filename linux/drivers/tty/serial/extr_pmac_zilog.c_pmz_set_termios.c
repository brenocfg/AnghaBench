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
struct uart_pmac_port {int dummy; } ;
struct ktermios {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZS_IS_OPEN (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  __pmz_set_termios (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  pmz_interrupt_control (struct uart_pmac_port*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static void pmz_set_termios(struct uart_port *port, struct ktermios *termios,
			    struct ktermios *old)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);	

	/* Disable IRQs on the port */
	pmz_interrupt_control(uap, 0);

	/* Setup new port configuration */
	__pmz_set_termios(port, termios, old);

	/* Re-enable IRQs on the port */
	if (ZS_IS_OPEN(uap))
		pmz_interrupt_control(uap, 1);

	spin_unlock_irqrestore(&port->lock, flags);
}