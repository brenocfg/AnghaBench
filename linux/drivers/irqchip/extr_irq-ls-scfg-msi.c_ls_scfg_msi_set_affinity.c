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
typedef  size_t u32 ;
struct ls_scfg_msi {size_t msir_num; TYPE_1__* msir; } ;
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;
struct TYPE_2__ {scalar_t__ gic_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int IRQ_SET_MASK_OK ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 size_t cpumask_any_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 size_t cpumask_first (struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_of (size_t) ; 
 struct ls_scfg_msi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_affinity_flag ; 
 int /*<<< orphan*/  pr_warn (char*,size_t) ; 

__attribute__((used)) static int ls_scfg_msi_set_affinity(struct irq_data *irq_data,
				    const struct cpumask *mask, bool force)
{
	struct ls_scfg_msi *msi_data = irq_data_get_irq_chip_data(irq_data);
	u32 cpu;

	if (!msi_affinity_flag)
		return -EINVAL;

	if (!force)
		cpu = cpumask_any_and(mask, cpu_online_mask);
	else
		cpu = cpumask_first(mask);

	if (cpu >= msi_data->msir_num)
		return -EINVAL;

	if (msi_data->msir[cpu].gic_irq <= 0) {
		pr_warn("cannot bind the irq to cpu%d\n", cpu);
		return -EINVAL;
	}

	irq_data_update_effective_affinity(irq_data, cpumask_of(cpu));

	return IRQ_SET_MASK_OK;
}