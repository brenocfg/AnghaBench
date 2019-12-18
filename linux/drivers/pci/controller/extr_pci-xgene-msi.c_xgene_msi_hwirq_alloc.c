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
struct xgene_msi_group {int /*<<< orphan*/  gic_irq; } ;
struct xgene_msi {struct xgene_msi_group* msi_groups; scalar_t__ num_cpus; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NR_HW_IRQS ; 
 scalar_t__ alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int irq_set_affinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int irq_set_handler_data (int /*<<< orphan*/ ,struct xgene_msi_group*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct xgene_msi xgene_msi_ctrl ; 
 int /*<<< orphan*/  xgene_msi_isr ; 

__attribute__((used)) static int xgene_msi_hwirq_alloc(unsigned int cpu)
{
	struct xgene_msi *msi = &xgene_msi_ctrl;
	struct xgene_msi_group *msi_group;
	cpumask_var_t mask;
	int i;
	int err;

	for (i = cpu; i < NR_HW_IRQS; i += msi->num_cpus) {
		msi_group = &msi->msi_groups[i];
		if (!msi_group->gic_irq)
			continue;

		irq_set_chained_handler(msi_group->gic_irq,
					xgene_msi_isr);
		err = irq_set_handler_data(msi_group->gic_irq, msi_group);
		if (err) {
			pr_err("failed to register GIC IRQ handler\n");
			return -EINVAL;
		}
		/*
		 * Statically allocate MSI GIC IRQs to each CPU core.
		 * With 8-core X-Gene v1, 2 MSI GIC IRQs are allocated
		 * to each core.
		 */
		if (alloc_cpumask_var(&mask, GFP_KERNEL)) {
			cpumask_clear(mask);
			cpumask_set_cpu(cpu, mask);
			err = irq_set_affinity(msi_group->gic_irq, mask);
			if (err)
				pr_err("failed to set affinity for GIC IRQ");
			free_cpumask_var(mask);
		} else {
			pr_err("failed to alloc CPU mask for affinity\n");
			err = -EINVAL;
		}

		if (err) {
			irq_set_chained_handler_and_data(msi_group->gic_irq,
							 NULL, NULL);
			return err;
		}
	}

	return 0;
}