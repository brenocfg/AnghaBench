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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __switch_to_tm (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  clear_task_ebb (struct task_struct*) ; 
 int /*<<< orphan*/  flush_all_to_thread (struct task_struct*) ; 

int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src)
{
	flush_all_to_thread(src);
	/*
	 * Flush TM state out so we can copy it.  __switch_to_tm() does this
	 * flush but it removes the checkpointed state from the current CPU and
	 * transitions the CPU out of TM mode.  Hence we need to call
	 * tm_recheckpoint_new_task() (on the same task) to restore the
	 * checkpointed state back and the TM mode.
	 *
	 * Can't pass dst because it isn't ready. Doesn't matter, passing
	 * dst is only important for __switch_to()
	 */
	__switch_to_tm(src, src);

	*dst = *src;

	clear_task_ebb(dst);

	return 0;
}