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
typedef  int u32 ;
struct uart_port {scalar_t__ membase; } ;
struct ltq_uart_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ASC_IRNCR_EIR ; 
 int ASC_IRNCR_MASK ; 
 int ASC_IRNCR_RIR ; 
 int ASC_IRNCR_TIR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ LTQ_ASC_IRNCR ; 
 int /*<<< orphan*/  lqasc_err_int (int,void*) ; 
 int /*<<< orphan*/  lqasc_rx_int (int,void*) ; 
 int /*<<< orphan*/  lqasc_tx_int (int,void*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t lqasc_irq(int irq, void *p)
{
	unsigned long flags;
	u32 stat;
	struct uart_port *port = p;
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	stat = readl(port->membase + LTQ_ASC_IRNCR);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	if (!(stat & ASC_IRNCR_MASK))
		return IRQ_NONE;

	if (stat & ASC_IRNCR_TIR)
		lqasc_tx_int(irq, p);

	if (stat & ASC_IRNCR_RIR)
		lqasc_rx_int(irq, p);

	if (stat & ASC_IRNCR_EIR)
		lqasc_err_int(irq, p);

	return IRQ_HANDLED;
}