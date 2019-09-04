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
typedef  size_t u64 ;
typedef  size_t u16 ;
struct task_struct {int dummy; } ;
struct TYPE_4__ {scalar_t__ ctx_id; int /*<<< orphan*/  tlb_gen; } ;
struct mm_struct {int /*<<< orphan*/  pgd; TYPE_1__ context; } ;
struct TYPE_6__ {int /*<<< orphan*/  loaded_mm_asid; int /*<<< orphan*/  loaded_mm; TYPE_2__* ctxs; int /*<<< orphan*/  is_lazy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tlb_gen; int /*<<< orphan*/  ctx_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PROVE_LOCKING ; 
 int /*<<< orphan*/  CONFIG_VMAP_STACK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 size_t LOADED_MM_SWITCHING ; 
 int /*<<< orphan*/  TLB_FLUSH_ALL ; 
 int /*<<< orphan*/  TLB_FLUSH_ON_TASK_SWITCH ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int /*<<< orphan*/  VM_WARN_ON_ONCE (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 size_t atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  choose_new_asid (struct mm_struct*,size_t,size_t*,int*) ; 
 int /*<<< orphan*/  cond_ibpb (struct task_struct*) ; 
 TYPE_3__ cpu_tlbstate ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,int /*<<< orphan*/ ) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  load_mm_cr4 (struct mm_struct*) ; 
 int /*<<< orphan*/  load_new_mm_cr3 (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  switch_ldt (struct mm_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  sync_current_stack_to_mm (struct mm_struct*) ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  trace_tlb_flush_rcuidle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void switch_mm_irqs_off(struct mm_struct *prev, struct mm_struct *next,
			struct task_struct *tsk)
{
	struct mm_struct *real_prev = this_cpu_read(cpu_tlbstate.loaded_mm);
	u16 prev_asid = this_cpu_read(cpu_tlbstate.loaded_mm_asid);
	unsigned cpu = smp_processor_id();
	u64 next_tlb_gen;

	/*
	 * NB: The scheduler will call us with prev == next when switching
	 * from lazy TLB mode to normal mode if active_mm isn't changing.
	 * When this happens, we don't assume that CR3 (and hence
	 * cpu_tlbstate.loaded_mm) matches next.
	 *
	 * NB: leave_mm() calls us with prev == NULL and tsk == NULL.
	 */

	/* We don't want flush_tlb_func_* to run concurrently with us. */
	if (IS_ENABLED(CONFIG_PROVE_LOCKING))
		WARN_ON_ONCE(!irqs_disabled());

	/*
	 * Verify that CR3 is what we think it is.  This will catch
	 * hypothetical buggy code that directly switches to swapper_pg_dir
	 * without going through leave_mm() / switch_mm_irqs_off() or that
	 * does something like write_cr3(read_cr3_pa()).
	 *
	 * Only do this check if CONFIG_DEBUG_VM=y because __read_cr3()
	 * isn't free.
	 */
#ifdef CONFIG_DEBUG_VM
	if (WARN_ON_ONCE(__read_cr3() != build_cr3(real_prev->pgd, prev_asid))) {
		/*
		 * If we were to BUG here, we'd be very likely to kill
		 * the system so hard that we don't see the call trace.
		 * Try to recover instead by ignoring the error and doing
		 * a global flush to minimize the chance of corruption.
		 *
		 * (This is far from being a fully correct recovery.
		 *  Architecturally, the CPU could prefetch something
		 *  back into an incorrect ASID slot and leave it there
		 *  to cause trouble down the road.  It's better than
		 *  nothing, though.)
		 */
		__flush_tlb_all();
	}
#endif
	this_cpu_write(cpu_tlbstate.is_lazy, false);

	/*
	 * The membarrier system call requires a full memory barrier and
	 * core serialization before returning to user-space, after
	 * storing to rq->curr. Writing to CR3 provides that full
	 * memory barrier and core serializing instruction.
	 */
	if (real_prev == next) {
		VM_WARN_ON(this_cpu_read(cpu_tlbstate.ctxs[prev_asid].ctx_id) !=
			   next->context.ctx_id);

		/*
		 * We don't currently support having a real mm loaded without
		 * our cpu set in mm_cpumask().  We have all the bookkeeping
		 * in place to figure out whether we would need to flush
		 * if our cpu were cleared in mm_cpumask(), but we don't
		 * currently use it.
		 */
		if (WARN_ON_ONCE(real_prev != &init_mm &&
				 !cpumask_test_cpu(cpu, mm_cpumask(next))))
			cpumask_set_cpu(cpu, mm_cpumask(next));

		return;
	} else {
		u16 new_asid;
		bool need_flush;

		/*
		 * Avoid user/user BTB poisoning by flushing the branch
		 * predictor when switching between processes. This stops
		 * one process from doing Spectre-v2 attacks on another.
		 */
		cond_ibpb(tsk);

		if (IS_ENABLED(CONFIG_VMAP_STACK)) {
			/*
			 * If our current stack is in vmalloc space and isn't
			 * mapped in the new pgd, we'll double-fault.  Forcibly
			 * map it.
			 */
			sync_current_stack_to_mm(next);
		}

		/*
		 * Stop remote flushes for the previous mm.
		 * Skip kernel threads; we never send init_mm TLB flushing IPIs,
		 * but the bitmap manipulation can cause cache line contention.
		 */
		if (real_prev != &init_mm) {
			VM_WARN_ON_ONCE(!cpumask_test_cpu(cpu,
						mm_cpumask(real_prev)));
			cpumask_clear_cpu(cpu, mm_cpumask(real_prev));
		}

		/*
		 * Start remote flushes and then read tlb_gen.
		 */
		if (next != &init_mm)
			cpumask_set_cpu(cpu, mm_cpumask(next));
		next_tlb_gen = atomic64_read(&next->context.tlb_gen);

		choose_new_asid(next, next_tlb_gen, &new_asid, &need_flush);

		/* Let nmi_uaccess_okay() know that we're changing CR3. */
		this_cpu_write(cpu_tlbstate.loaded_mm, LOADED_MM_SWITCHING);
		barrier();

		if (need_flush) {
			this_cpu_write(cpu_tlbstate.ctxs[new_asid].ctx_id, next->context.ctx_id);
			this_cpu_write(cpu_tlbstate.ctxs[new_asid].tlb_gen, next_tlb_gen);
			load_new_mm_cr3(next->pgd, new_asid, true);

			/*
			 * NB: This gets called via leave_mm() in the idle path
			 * where RCU functions differently.  Tracing normally
			 * uses RCU, so we need to use the _rcuidle variant.
			 *
			 * (There is no good reason for this.  The idle code should
			 *  be rearranged to call this before rcu_idle_enter().)
			 */
			trace_tlb_flush_rcuidle(TLB_FLUSH_ON_TASK_SWITCH, TLB_FLUSH_ALL);
		} else {
			/* The new ASID is already up to date. */
			load_new_mm_cr3(next->pgd, new_asid, false);

			/* See above wrt _rcuidle. */
			trace_tlb_flush_rcuidle(TLB_FLUSH_ON_TASK_SWITCH, 0);
		}

		/* Make sure we write CR3 before loaded_mm. */
		barrier();

		this_cpu_write(cpu_tlbstate.loaded_mm, next);
		this_cpu_write(cpu_tlbstate.loaded_mm_asid, new_asid);
	}

	load_mm_cr4(next);
	switch_ldt(real_prev, next);
}