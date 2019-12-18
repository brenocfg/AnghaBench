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
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 int GIC_MAP_PIN_MAP_TO_PIN ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int gic_cpu_pin ; 
 int /*<<< orphan*/  gic_lock ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  mips_cm_vp_id (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_gic_map_pin (int,int) ; 
 int /*<<< orphan*/  write_gic_map_vp (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gic_shared_irq_domain_map(struct irq_domain *d, unsigned int virq,
				     irq_hw_number_t hw, unsigned int cpu)
{
	int intr = GIC_HWIRQ_TO_SHARED(hw);
	struct irq_data *data;
	unsigned long flags;

	data = irq_get_irq_data(virq);

	spin_lock_irqsave(&gic_lock, flags);
	write_gic_map_pin(intr, GIC_MAP_PIN_MAP_TO_PIN | gic_cpu_pin);
	write_gic_map_vp(intr, BIT(mips_cm_vp_id(cpu)));
	irq_data_update_effective_affinity(data, cpumask_of(cpu));
	spin_unlock_irqrestore(&gic_lock, flags);

	return 0;
}