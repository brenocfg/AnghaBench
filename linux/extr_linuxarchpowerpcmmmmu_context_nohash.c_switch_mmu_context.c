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
struct task_struct {int dummy; } ;
struct TYPE_2__ {unsigned int id; int /*<<< orphan*/  active; } ;
struct mm_struct {int /*<<< orphan*/  pgd; TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_8xx ; 
 unsigned int FIRST_CONTEXT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int LAST_CONTEXT ; 
 unsigned int MMU_NO_CONTEXT ; 
 scalar_t__ __test_and_set_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  context_check_map () ; 
 int /*<<< orphan*/  context_lock ; 
 unsigned long* context_map ; 
 struct mm_struct** context_mm ; 
 int /*<<< orphan*/  cpu ; 
 unsigned int find_next_zero_bit (unsigned long*,unsigned int,unsigned int) ; 
 scalar_t__ likely (int) ; 
 unsigned int next_context ; 
 scalar_t__ nr_free_contexts ; 
 int /*<<< orphan*/  pr_hard (char*,int /*<<< orphan*/ ,struct mm_struct*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_hardcont (char*,unsigned int,...) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_context (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int steal_all_contexts () ; 
 unsigned int steal_context_up (unsigned int) ; 

void switch_mmu_context(struct mm_struct *prev, struct mm_struct *next,
			struct task_struct *tsk)
{
	unsigned int id;
#ifdef CONFIG_SMP
	unsigned int i, cpu = smp_processor_id();
#endif
	unsigned long *map;

	/* No lockless fast path .. yet */
	raw_spin_lock(&context_lock);

	pr_hard("[%d] activating context for mm @%p, active=%d, id=%d",
		cpu, next, next->context.active, next->context.id);

#ifdef CONFIG_SMP
	/* Mark us active and the previous one not anymore */
	next->context.active++;
	if (prev) {
		pr_hardcont(" (old=0x%p a=%d)", prev, prev->context.active);
		WARN_ON(prev->context.active < 1);
		prev->context.active--;
	}

 again:
#endif /* CONFIG_SMP */

	/* If we already have a valid assigned context, skip all that */
	id = next->context.id;
	if (likely(id != MMU_NO_CONTEXT)) {
#ifdef DEBUG_MAP_CONSISTENCY
		if (context_mm[id] != next)
			pr_err("MMU: mm 0x%p has id %d but context_mm[%d] says 0x%p\n",
			       next, id, id, context_mm[id]);
#endif
		goto ctxt_ok;
	}

	/* We really don't have a context, let's try to acquire one */
	id = next_context;
	if (id > LAST_CONTEXT)
		id = FIRST_CONTEXT;
	map = context_map;

	/* No more free contexts, let's try to steal one */
	if (nr_free_contexts == 0) {
#ifdef CONFIG_SMP
		if (num_online_cpus() > 1) {
			id = steal_context_smp(id);
			if (id == MMU_NO_CONTEXT)
				goto again;
			goto stolen;
		}
#endif /* CONFIG_SMP */
		if (IS_ENABLED(CONFIG_PPC_8xx))
			id = steal_all_contexts();
		else
			id = steal_context_up(id);
		goto stolen;
	}
	nr_free_contexts--;

	/* We know there's at least one free context, try to find it */
	while (__test_and_set_bit(id, map)) {
		id = find_next_zero_bit(map, LAST_CONTEXT+1, id);
		if (id > LAST_CONTEXT)
			id = FIRST_CONTEXT;
	}
 stolen:
	next_context = id + 1;
	context_mm[id] = next;
	next->context.id = id;
	pr_hardcont(" | new id=%d,nrf=%d", id, nr_free_contexts);

	context_check_map();
 ctxt_ok:

	/* If that context got marked stale on this CPU, then flush the
	 * local TLB for it and unmark it before we use it
	 */
#ifdef CONFIG_SMP
	if (test_bit(id, stale_map[cpu])) {
		pr_hardcont(" | stale flush %d [%d..%d]",
			    id, cpu_first_thread_sibling(cpu),
			    cpu_last_thread_sibling(cpu));

		local_flush_tlb_mm(next);

		/* XXX This clear should ultimately be part of local_flush_tlb_mm */
		for (i = cpu_first_thread_sibling(cpu);
		     i <= cpu_last_thread_sibling(cpu); i++) {
			if (stale_map[i])
				__clear_bit(id, stale_map[i]);
		}
	}
#endif

	/* Flick the MMU and release lock */
	pr_hardcont(" -> %d\n", id);
	set_context(id, next->pgd);
	raw_spin_unlock(&context_lock);
}