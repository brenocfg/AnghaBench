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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {int /*<<< orphan*/  execlists; TYPE_1__ timeline; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_PREEMPT ; 
 int /*<<< orphan*/  execlists_dequeue (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  execlists_is_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_csb (struct intel_engine_cs* const) ; 

__attribute__((used)) static void __execlists_submission_tasklet(struct intel_engine_cs *const engine)
{
	lockdep_assert_held(&engine->timeline.lock);

	process_csb(engine);
	if (!execlists_is_active(&engine->execlists, EXECLISTS_ACTIVE_PREEMPT))
		execlists_dequeue(engine);
}