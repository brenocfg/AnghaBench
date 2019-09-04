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
struct mm_struct {int /*<<< orphan*/  mm_count; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_running ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 int /*<<< orphan*/  openrisc_clockevent_init () ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 int /*<<< orphan*/  setup_cpuinfo () ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  synchronise_count_slave (unsigned int) ; 

void secondary_start_kernel(void)
{
	struct mm_struct *mm = &init_mm;
	unsigned int cpu = smp_processor_id();
	/*
	 * All kernel threads share the same mm context; grab a
	 * reference and switch to it.
	 */
	atomic_inc(&mm->mm_count);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	pr_info("CPU%u: Booted secondary processor\n", cpu);

	setup_cpuinfo();
	openrisc_clockevent_init();

	notify_cpu_starting(cpu);

	/*
	 * OK, now it's safe to let the boot CPU continue
	 */
	complete(&cpu_running);

	synchronise_count_slave(cpu);
	set_cpu_online(cpu, true);

	local_irq_enable();

	preempt_disable();
	/*
	 * OK, it's off to the idle thread for us
	 */
	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}