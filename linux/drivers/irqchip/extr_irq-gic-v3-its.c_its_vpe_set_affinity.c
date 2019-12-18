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
struct its_vpe {int col_idx; } ;
struct irq_data {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int IRQ_SET_MASK_OK_DONE ; 
 int cpumask_first (struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 struct its_vpe* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_send_vmovp (struct its_vpe*) ; 
 int /*<<< orphan*/  its_vpe_db_proxy_move (struct its_vpe*,int,int) ; 

__attribute__((used)) static int its_vpe_set_affinity(struct irq_data *d,
				const struct cpumask *mask_val,
				bool force)
{
	struct its_vpe *vpe = irq_data_get_irq_chip_data(d);
	int cpu = cpumask_first(mask_val);

	/*
	 * Changing affinity is mega expensive, so let's be as lazy as
	 * we can and only do it if we really have to. Also, if mapped
	 * into the proxy device, we need to move the doorbell
	 * interrupt to its new location.
	 */
	if (vpe->col_idx != cpu) {
		int from = vpe->col_idx;

		vpe->col_idx = cpu;
		its_send_vmovp(vpe);
		its_vpe_db_proxy_move(vpe, from, cpu);
	}

	irq_data_update_effective_affinity(d, cpumask_of(cpu));

	return IRQ_SET_MASK_OK_DONE;
}