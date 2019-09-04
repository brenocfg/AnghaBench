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
struct task_struct {unsigned long mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_user_mm; int /*<<< orphan*/  last_user_mm_ibpb; } ;

/* Variables and functions */
 unsigned long LAST_USER_MM_IBPB ; 
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  indirect_branch_prediction_barrier () ; 
 unsigned long mm_mangle_tif_spec_ib (struct task_struct*) ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_mm_always_ibpb ; 
 int /*<<< orphan*/  switch_mm_cond_ibpb ; 
 unsigned long this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cond_ibpb(struct task_struct *next)
{
	if (!next || !next->mm)
		return;

	/*
	 * Both, the conditional and the always IBPB mode use the mm
	 * pointer to avoid the IBPB when switching between tasks of the
	 * same process. Using the mm pointer instead of mm->context.ctx_id
	 * opens a hypothetical hole vs. mm_struct reuse, which is more or
	 * less impossible to control by an attacker. Aside of that it
	 * would only affect the first schedule so the theoretically
	 * exposed data is not really interesting.
	 */
	if (static_branch_likely(&switch_mm_cond_ibpb)) {
		unsigned long prev_mm, next_mm;

		/*
		 * This is a bit more complex than the always mode because
		 * it has to handle two cases:
		 *
		 * 1) Switch from a user space task (potential attacker)
		 *    which has TIF_SPEC_IB set to a user space task
		 *    (potential victim) which has TIF_SPEC_IB not set.
		 *
		 * 2) Switch from a user space task (potential attacker)
		 *    which has TIF_SPEC_IB not set to a user space task
		 *    (potential victim) which has TIF_SPEC_IB set.
		 *
		 * This could be done by unconditionally issuing IBPB when
		 * a task which has TIF_SPEC_IB set is either scheduled in
		 * or out. Though that results in two flushes when:
		 *
		 * - the same user space task is scheduled out and later
		 *   scheduled in again and only a kernel thread ran in
		 *   between.
		 *
		 * - a user space task belonging to the same process is
		 *   scheduled in after a kernel thread ran in between
		 *
		 * - a user space task belonging to the same process is
		 *   scheduled in immediately.
		 *
		 * Optimize this with reasonably small overhead for the
		 * above cases. Mangle the TIF_SPEC_IB bit into the mm
		 * pointer of the incoming task which is stored in
		 * cpu_tlbstate.last_user_mm_ibpb for comparison.
		 */
		next_mm = mm_mangle_tif_spec_ib(next);
		prev_mm = this_cpu_read(cpu_tlbstate.last_user_mm_ibpb);

		/*
		 * Issue IBPB only if the mm's are different and one or
		 * both have the IBPB bit set.
		 */
		if (next_mm != prev_mm &&
		    (next_mm | prev_mm) & LAST_USER_MM_IBPB)
			indirect_branch_prediction_barrier();

		this_cpu_write(cpu_tlbstate.last_user_mm_ibpb, next_mm);
	}

	if (static_branch_unlikely(&switch_mm_always_ibpb)) {
		/*
		 * Only flush when switching to a user space task with a
		 * different context than the user space task which ran
		 * last on this CPU.
		 */
		if (this_cpu_read(cpu_tlbstate.last_user_mm) != next->mm) {
			indirect_branch_prediction_barrier();
			this_cpu_write(cpu_tlbstate.last_user_mm, next->mm);
		}
	}
}