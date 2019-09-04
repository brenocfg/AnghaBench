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
struct intel_wait {int dummy; } ;
struct igt_wakeup {int /*<<< orphan*/  engine; int /*<<< orphan*/  flags; int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_add_wait (int /*<<< orphan*/ ,struct intel_wait*) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_remove_wait (int /*<<< orphan*/ ,struct intel_wait*) ; 
 int /*<<< orphan*/  intel_wait_init_for_seqno (struct intel_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_ready (struct igt_wakeup*) ; 

__attribute__((used)) static int igt_wakeup_thread(void *arg)
{
	struct igt_wakeup *w = arg;
	struct intel_wait wait;

	while (wait_for_ready(w)) {
		GEM_BUG_ON(kthread_should_stop());

		intel_wait_init_for_seqno(&wait, w->seqno);
		intel_engine_add_wait(w->engine, &wait);
		for (;;) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			if (i915_seqno_passed(intel_engine_get_seqno(w->engine),
					      w->seqno))
				break;

			if (test_bit(STOP, &w->flags)) /* emergency escape */
				break;

			schedule();
		}
		intel_engine_remove_wait(w->engine, &wait);
		__set_current_state(TASK_RUNNING);
	}

	return 0;
}