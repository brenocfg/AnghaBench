#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pending; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_2__ execlists; TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  execlists_dequeue (struct intel_engine_cs* const) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void __execlists_submission_tasklet(struct intel_engine_cs *const engine)
{
	lockdep_assert_held(&engine->active.lock);
	if (!engine->execlists.pending[0]) {
		rcu_read_lock(); /* protect peeking at execlists->active */
		execlists_dequeue(engine);
		rcu_read_unlock();
	}
}