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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct cpumask {int dummy; } ;
struct apic_chip_data {int is_managed; } ;

/* Variables and functions */
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 struct cpumask* irq_data_get_affinity_mask (struct irq_data*) ; 
 int irq_matrix_reserve_managed (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vector_reserve_managed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vector_lock ; 
 int /*<<< orphan*/  vector_matrix ; 

__attribute__((used)) static int reserve_managed_vector(struct irq_data *irqd)
{
	const struct cpumask *affmsk = irq_data_get_affinity_mask(irqd);
	struct apic_chip_data *apicd = apic_chip_data(irqd);
	unsigned long flags;
	int ret;

	raw_spin_lock_irqsave(&vector_lock, flags);
	apicd->is_managed = true;
	ret = irq_matrix_reserve_managed(vector_matrix, affmsk);
	raw_spin_unlock_irqrestore(&vector_lock, flags);
	trace_vector_reserve_managed(irqd->irq, ret);
	return ret;
}