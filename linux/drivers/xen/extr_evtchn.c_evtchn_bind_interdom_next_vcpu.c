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
struct TYPE_2__ {int /*<<< orphan*/  affinity; } ;
struct irq_desc {int /*<<< orphan*/  lock; TYPE_1__ irq_common_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bind_last_selected_cpu ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 unsigned int cpumask_first_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int cpumask_next_and (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int irq_from_evtchn (int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_set_affinity_evtchn (struct irq_desc*,unsigned int) ; 

__attribute__((used)) static void evtchn_bind_interdom_next_vcpu(int evtchn)
{
	unsigned int selected_cpu, irq;
	struct irq_desc *desc;
	unsigned long flags;

	irq = irq_from_evtchn(evtchn);
	desc = irq_to_desc(irq);

	if (!desc)
		return;

	raw_spin_lock_irqsave(&desc->lock, flags);
	selected_cpu = this_cpu_read(bind_last_selected_cpu);
	selected_cpu = cpumask_next_and(selected_cpu,
			desc->irq_common_data.affinity, cpu_online_mask);

	if (unlikely(selected_cpu >= nr_cpu_ids))
		selected_cpu = cpumask_first_and(desc->irq_common_data.affinity,
				cpu_online_mask);

	this_cpu_write(bind_last_selected_cpu, selected_cpu);

	/* unmask expects irqs to be disabled */
	xen_set_affinity_evtchn(desc, selected_cpu);
	raw_spin_unlock_irqrestore(&desc->lock, flags);
}