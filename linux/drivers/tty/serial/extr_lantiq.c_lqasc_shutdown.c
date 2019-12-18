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
struct ltq_uart_port {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_irq ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASCRXFCON_RXFEN ; 
 int /*<<< orphan*/  ASCRXFCON_RXFFLU ; 
 int /*<<< orphan*/  ASCTXFCON_TXFEN ; 
 int /*<<< orphan*/  ASCTXFCON_TXFFLU ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ LTQ_ASC_CON ; 
 scalar_t__ LTQ_ASC_RXFCON ; 
 scalar_t__ LTQ_ASC_TXFCON ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  asc_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 struct ltq_uart_port* to_ltq_uart_port (struct uart_port*) ; 

__attribute__((used)) static void
lqasc_shutdown(struct uart_port *port)
{
	struct ltq_uart_port *ltq_port = to_ltq_uart_port(port);
	unsigned long flags;

	ltq_port->soc->free_irq(port);

	spin_lock_irqsave(&ltq_port->lock, flags);
	__raw_writel(0, port->membase + LTQ_ASC_CON);
	asc_update_bits(ASCRXFCON_RXFEN, ASCRXFCON_RXFFLU,
		port->membase + LTQ_ASC_RXFCON);
	asc_update_bits(ASCTXFCON_TXFEN, ASCTXFCON_TXFFLU,
		port->membase + LTQ_ASC_TXFCON);
	spin_unlock_irqrestore(&ltq_port->lock, flags);
	if (!IS_ERR(ltq_port->clk))
		clk_disable_unprepare(ltq_port->clk);
}