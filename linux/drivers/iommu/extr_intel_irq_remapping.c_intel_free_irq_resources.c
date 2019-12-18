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
struct irq_data {struct intel_ir_data* chip_data; } ;
struct irq_2_iommu {int dummy; } ;
struct intel_ir_data {struct irq_2_iommu irq_2_iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_entries (struct irq_2_iommu*) ; 
 int /*<<< orphan*/  irq_2_ir_lock ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_reset_irq_data (struct irq_data*) ; 
 int /*<<< orphan*/  kfree (struct intel_ir_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void intel_free_irq_resources(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs)
{
	struct irq_data *irq_data;
	struct intel_ir_data *data;
	struct irq_2_iommu *irq_iommu;
	unsigned long flags;
	int i;
	for (i = 0; i < nr_irqs; i++) {
		irq_data = irq_domain_get_irq_data(domain, virq  + i);
		if (irq_data && irq_data->chip_data) {
			data = irq_data->chip_data;
			irq_iommu = &data->irq_2_iommu;
			raw_spin_lock_irqsave(&irq_2_ir_lock, flags);
			clear_entries(irq_iommu);
			raw_spin_unlock_irqrestore(&irq_2_ir_lock, flags);
			irq_domain_reset_irq_data(irq_data);
			kfree(data);
		}
	}
}