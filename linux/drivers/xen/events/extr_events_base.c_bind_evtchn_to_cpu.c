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
struct irq_info {unsigned int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int get_evtchn_to_irq (unsigned int) ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/  irq_get_affinity_mask (int) ; 
 int /*<<< orphan*/  xen_evtchn_port_bind_to_cpu (struct irq_info*,unsigned int) ; 

__attribute__((used)) static void bind_evtchn_to_cpu(unsigned int chn, unsigned int cpu)
{
	int irq = get_evtchn_to_irq(chn);
	struct irq_info *info = info_for_irq(irq);

	BUG_ON(irq == -1);
#ifdef CONFIG_SMP
	cpumask_copy(irq_get_affinity_mask(irq), cpumask_of(cpu));
#endif
	xen_evtchn_port_bind_to_cpu(info, cpu);

	info->cpu = cpu;
}