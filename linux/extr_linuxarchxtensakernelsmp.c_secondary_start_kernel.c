#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int dummy; } ;
struct TYPE_3__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  calibrate_delay () ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_running ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  enter_lazy_tlb (struct mm_struct*,TYPE_1__*) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  init_mmu () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_timer_setup (unsigned int) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  mmget (struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  secondary_init_irq () ; 
 int /*<<< orphan*/  secondary_trap_init () ; 
 int /*<<< orphan*/  set_cpu_online (unsigned int,int) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  trace_hardirqs_off () ; 

void secondary_start_kernel(void)
{
	struct mm_struct *mm = &init_mm;
	unsigned int cpu = smp_processor_id();

	init_mmu();

#ifdef CONFIG_DEBUG_KERNEL
	if (boot_secondary_processors == 0) {
		pr_debug("%s: boot_secondary_processors:%d; Hanging cpu:%d\n",
			__func__, boot_secondary_processors, cpu);
		for (;;)
			__asm__ __volatile__ ("waiti " __stringify(LOCKLEVEL));
	}

	pr_debug("%s: boot_secondary_processors:%d; Booting cpu:%d\n",
		__func__, boot_secondary_processors, cpu);
#endif
	/* Init EXCSAVE1 */

	secondary_trap_init();

	/* All kernel threads share the same mm context. */

	mmget(mm);
	mmgrab(mm);
	current->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	enter_lazy_tlb(mm, current);

	preempt_disable();
	trace_hardirqs_off();

	calibrate_delay();

	notify_cpu_starting(cpu);

	secondary_init_irq();
	local_timer_setup(cpu);

	set_cpu_online(cpu, true);

	local_irq_enable();

	complete(&cpu_running);

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
}