#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {unsigned int vector; int /*<<< orphan*/  dest_apicid; } ;
struct apic_chip_data {TYPE_1__ hw_irq_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* calc_dest_apicid ) (unsigned int) ;} ;

/* Variables and functions */
 TYPE_2__* apic ; 
 struct apic_chip_data* apic_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  irq_data_update_effective_affinity (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  trace_vector_config (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_lock ; 

__attribute__((used)) static void apic_update_irq_cfg(struct irq_data *irqd, unsigned int vector,
				unsigned int cpu)
{
	struct apic_chip_data *apicd = apic_chip_data(irqd);

	lockdep_assert_held(&vector_lock);

	apicd->hw_irq_cfg.vector = vector;
	apicd->hw_irq_cfg.dest_apicid = apic->calc_dest_apicid(cpu);
	irq_data_update_effective_affinity(irqd, cpumask_of(cpu));
	trace_vector_config(irqd->irq, vector, cpu,
			    apicd->hw_irq_cfg.dest_apicid);
}