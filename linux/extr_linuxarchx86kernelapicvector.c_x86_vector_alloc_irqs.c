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
struct irq_data {unsigned int hwirq; struct apic_chip_data* chip_data; int /*<<< orphan*/ * chip; } ;
struct irq_alloc_info {int flags; } ;
struct apic_chip_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int ENXIO ; 
 int /*<<< orphan*/  WARN_ON_ONCE (struct apic_chip_data*) ; 
 int X86_IRQ_ALLOC_CONTIGUOUS_VECTORS ; 
 int X86_IRQ_ALLOC_LEGACY ; 
 struct apic_chip_data* alloc_apic_chip_data (int) ; 
 int assign_irq_vector_policy (struct irq_data*,struct irq_alloc_info*) ; 
 scalar_t__ disable_apic ; 
 int /*<<< orphan*/  free_apic_chip_data (struct apic_chip_data*) ; 
 int irq_data_get_node (struct irq_data*) ; 
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irqd_set_single_target (struct irq_data*) ; 
 int /*<<< orphan*/  lapic_controller ; 
 int /*<<< orphan*/  trace_vector_setup (unsigned int,int,int) ; 
 int /*<<< orphan*/  vector_configure_legacy (unsigned int,struct irq_data*,struct apic_chip_data*) ; 
 int /*<<< orphan*/  x86_vector_free_irqs (struct irq_domain*,unsigned int,int) ; 

__attribute__((used)) static int x86_vector_alloc_irqs(struct irq_domain *domain, unsigned int virq,
				 unsigned int nr_irqs, void *arg)
{
	struct irq_alloc_info *info = arg;
	struct apic_chip_data *apicd;
	struct irq_data *irqd;
	int i, err, node;

	if (disable_apic)
		return -ENXIO;

	/* Currently vector allocator can't guarantee contiguous allocations */
	if ((info->flags & X86_IRQ_ALLOC_CONTIGUOUS_VECTORS) && nr_irqs > 1)
		return -ENOSYS;

	for (i = 0; i < nr_irqs; i++) {
		irqd = irq_domain_get_irq_data(domain, virq + i);
		BUG_ON(!irqd);
		node = irq_data_get_node(irqd);
		WARN_ON_ONCE(irqd->chip_data);
		apicd = alloc_apic_chip_data(node);
		if (!apicd) {
			err = -ENOMEM;
			goto error;
		}

		apicd->irq = virq + i;
		irqd->chip = &lapic_controller;
		irqd->chip_data = apicd;
		irqd->hwirq = virq + i;
		irqd_set_single_target(irqd);
		/*
		 * Legacy vectors are already assigned when the IOAPIC
		 * takes them over. They stay on the same vector. This is
		 * required for check_timer() to work correctly as it might
		 * switch back to legacy mode. Only update the hardware
		 * config.
		 */
		if (info->flags & X86_IRQ_ALLOC_LEGACY) {
			if (!vector_configure_legacy(virq + i, irqd, apicd))
				continue;
		}

		err = assign_irq_vector_policy(irqd, info);
		trace_vector_setup(virq + i, false, err);
		if (err) {
			irqd->chip_data = NULL;
			free_apic_chip_data(apicd);
			goto error;
		}
	}

	return 0;

error:
	x86_vector_free_irqs(domain, virq, i);
	return err;
}