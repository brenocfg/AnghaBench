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
struct irq_domain {int dummy; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct apic_chip_data {scalar_t__ can_reserve; scalar_t__ has_reserved; int /*<<< orphan*/  is_managed; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  clear_irq_vector (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  reserve_irq_vector_locked (struct irq_data*) ; 
 int /*<<< orphan*/  trace_vector_deactivate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  vector_assign_managed_shutdown (struct irq_data*) ; 
 int /*<<< orphan*/  vector_lock ; 

__attribute__((used)) static void x86_vector_deactivate(struct irq_domain *dom, struct irq_data *irqd)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	unsigned long flags;

	trace_vector_deactivate(irqd->irq, apicd->is_managed,
				apicd->can_reserve, false);

	/* Regular fixed assigned interrupt */
	if (!apicd->is_managed && !apicd->can_reserve)
		return;
	/* If the interrupt has a global reservation, nothing to do */
	if (apicd->has_reserved)
		return;

	raw_spin_lock_irqsave(&vector_lock, flags);
	clear_irq_vector(irqd);
	if (apicd->can_reserve)
		reserve_irq_vector_locked(irqd);
	else
		vector_assign_managed_shutdown(irqd);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
}