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
struct zs_scc {int /*<<< orphan*/  irq_guard; int /*<<< orphan*/  zlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct zs_port {TYPE_1__ port; int /*<<< orphan*/ * regs; struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  RxENABLE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct zs_scc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_shutdown(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	unsigned long flags;
	int irq_guard;

	spin_lock_irqsave(&scc->zlock, flags);

	zport->regs[3] &= ~RxENABLE;
	write_zsreg(zport, R5, zport->regs[5]);
	write_zsreg(zport, R3, zport->regs[3]);

	spin_unlock_irqrestore(&scc->zlock, flags);

	irq_guard = atomic_add_return(-1, &scc->irq_guard);
	if (!irq_guard)
		free_irq(zport->port.irq, scc);
}