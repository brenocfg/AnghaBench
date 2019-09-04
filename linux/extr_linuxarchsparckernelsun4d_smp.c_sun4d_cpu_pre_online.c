#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * active_mm; } ;
struct TYPE_5__ {int cpu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tlb_all ) () ;int /*<<< orphan*/  (* cache_all ) () ;} ;

/* Variables and functions */
 unsigned long PAGE_OFFSET ; 
 int /*<<< orphan*/  barrier () ; 
 int cc_get_imsk () ; 
 int /*<<< orphan*/  cc_set_imsk (int) ; 
 int /*<<< orphan*/ * cpu_callin_map ; 
 int* cpu_leds ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 TYPE_2__** current_set ; 
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  init_mm ; 
 TYPE_1__* local_ops ; 
 int /*<<< orphan*/  mmgrab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_leds (int) ; 
 int /*<<< orphan*/  smp_commenced_mask ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  sun4d_imsk_lock ; 
 int /*<<< orphan*/  sun4d_swap (unsigned long*,int) ; 

void sun4d_cpu_pre_online(void *arg)
{
	unsigned long flags;
	int cpuid;

	cpuid = hard_smp_processor_id();

	/* Unblock the master CPU _only_ when the scheduler state
	 * of all secondary CPUs will be up-to-date, so after
	 * the SMP initialization the master will be just allowed
	 * to call the scheduler code.
	 */
	sun4d_swap((unsigned long *)&cpu_callin_map[cpuid], 1);
	local_ops->cache_all();
	local_ops->tlb_all();

	while ((unsigned long)current_set[cpuid] < PAGE_OFFSET)
		barrier();

	while (current_set[cpuid]->cpu != cpuid)
		barrier();

	/* Fix idle thread fields. */
	__asm__ __volatile__("ld [%0], %%g6\n\t"
			     : : "r" (&current_set[cpuid])
			     : "memory" /* paranoid */);

	cpu_leds[cpuid] = 0x9;
	show_leds(cpuid);

	/* Attach to the address space of init_task. */
	mmgrab(&init_mm);
	current->active_mm = &init_mm;

	local_ops->cache_all();
	local_ops->tlb_all();

	while (!cpumask_test_cpu(cpuid, &smp_commenced_mask))
		barrier();

	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk(cc_get_imsk() & ~0x4000); /* Allow PIL 14 as well */
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
}