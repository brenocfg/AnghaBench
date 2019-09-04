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
struct mce {int inject_flags; scalar_t__ status; } ;

/* Variables and functions */
 int MCJ_EXCEPTION ; 
 int NMI_DONE ; 
 int NMI_HANDLED ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  injectm ; 
 int /*<<< orphan*/  mce_inject_cpumask ; 
 int /*<<< orphan*/  raise_exception (struct mce*,struct pt_regs*) ; 
 int /*<<< orphan*/  raise_poll (struct mce*) ; 
 int smp_processor_id () ; 
 struct mce* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mce_raise_notify(unsigned int cmd, struct pt_regs *regs)
{
	int cpu = smp_processor_id();
	struct mce *m = this_cpu_ptr(&injectm);
	if (!cpumask_test_cpu(cpu, mce_inject_cpumask))
		return NMI_DONE;
	cpumask_clear_cpu(cpu, mce_inject_cpumask);
	if (m->inject_flags & MCJ_EXCEPTION)
		raise_exception(m, regs);
	else if (m->status)
		raise_poll(m);
	return NMI_HANDLED;
}