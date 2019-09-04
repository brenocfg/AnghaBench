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
struct intel_wait {int /*<<< orphan*/  node; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  rb_lock; int /*<<< orphan*/  irq_wait; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 struct intel_wait* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __intel_engine_remove_wait (struct intel_engine_cs*,struct intel_wait*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_engine_remove_wait(struct intel_engine_cs *engine,
			      struct intel_wait *wait)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	/* Quick check to see if this waiter was already decoupled from
	 * the tree by the bottom-half to avoid contention on the spinlock
	 * by the herd.
	 */
	if (RB_EMPTY_NODE(&wait->node)) {
		GEM_BUG_ON(READ_ONCE(b->irq_wait) == wait);
		return;
	}

	spin_lock_irq(&b->rb_lock);
	__intel_engine_remove_wait(engine, wait);
	spin_unlock_irq(&b->rb_lock);
}