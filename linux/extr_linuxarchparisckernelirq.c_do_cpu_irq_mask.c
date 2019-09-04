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
struct pt_regs {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 unsigned long cpu_eiem ; 
 int eirr_to_irq (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int /*<<< orphan*/  irq_data_to_desc (struct irq_data*) ; 
 int /*<<< orphan*/  irq_desc_has_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int /*<<< orphan*/  local_ack_eiem ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 unsigned long mfctl (int) ; 
 unsigned long per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_eiem (unsigned long) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stack_overflow_check (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 

void do_cpu_irq_mask(struct pt_regs *regs)
{
	struct pt_regs *old_regs;
	unsigned long eirr_val;
	int irq, cpu = smp_processor_id();
	struct irq_data *irq_data;
#ifdef CONFIG_SMP
	cpumask_t dest;
#endif

	old_regs = set_irq_regs(regs);
	local_irq_disable();
	irq_enter();

	eirr_val = mfctl(23) & cpu_eiem & per_cpu(local_ack_eiem, cpu);
	if (!eirr_val)
		goto set_out;
	irq = eirr_to_irq(eirr_val);

	irq_data = irq_get_irq_data(irq);

	/* Filter out spurious interrupts, mostly from serial port at bootup */
	if (unlikely(!irq_desc_has_action(irq_data_to_desc(irq_data))))
		goto set_out;

#ifdef CONFIG_SMP
	cpumask_copy(&dest, irq_data_get_affinity_mask(irq_data));
	if (irqd_is_per_cpu(irq_data) &&
	    !cpumask_test_cpu(smp_processor_id(), &dest)) {
		int cpu = cpumask_first(&dest);

		printk(KERN_DEBUG "redirecting irq %d from CPU %d to %d\n",
		       irq, smp_processor_id(), cpu);
		gsc_writel(irq + CPU_IRQ_BASE,
			   per_cpu(cpu_data, cpu).hpa);
		goto set_out;
	}
#endif
	stack_overflow_check(regs);

#ifdef CONFIG_IRQSTACKS
	execute_on_irq_stack(&generic_handle_irq, irq);
#else
	generic_handle_irq(irq);
#endif /* CONFIG_IRQSTACKS */

 out:
	irq_exit();
	set_irq_regs(old_regs);
	return;

 set_out:
	set_eiem(cpu_eiem & per_cpu(local_ack_eiem, cpu));
	goto out;
}