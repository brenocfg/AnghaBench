#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  bits; } ;
struct TYPE_8__ {TYPE_2__ icache_stale_mask; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  TYPE_2__ cpumask_t ;
struct TYPE_10__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_andnot (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,TYPE_2__*) ; 
 int cpumask_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  cpumask_setall (TYPE_2__*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  local_flush_icache_all () ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  sbi_remote_fence_i (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 unsigned int smp_processor_id () ; 

void flush_icache_mm(struct mm_struct *mm, bool local)
{
	unsigned int cpu;
	cpumask_t others, *mask;

	preempt_disable();

	/* Mark every hart's icache as needing a flush for this MM. */
	mask = &mm->context.icache_stale_mask;
	cpumask_setall(mask);
	/* Flush this hart's I$ now, and mark it as flushed. */
	cpu = smp_processor_id();
	cpumask_clear_cpu(cpu, mask);
	local_flush_icache_all();

	/*
	 * Flush the I$ of other harts concurrently executing, and mark them as
	 * flushed.
	 */
	cpumask_andnot(&others, mm_cpumask(mm), cpumask_of(cpu));
	local |= cpumask_empty(&others);
	if (mm != current->active_mm || !local)
		sbi_remote_fence_i(others.bits);
	else {
		/*
		 * It's assumed that at least one strongly ordered operation is
		 * performed on this hart between setting a hart's cpumask bit
		 * and scheduling this MM context on that hart.  Sending an SBI
		 * remote message will do this, but in the case where no
		 * messages are sent we still need to order this hart's writes
		 * with flush_icache_deferred().
		 */
		smp_mb();
	}

	preempt_enable();
}