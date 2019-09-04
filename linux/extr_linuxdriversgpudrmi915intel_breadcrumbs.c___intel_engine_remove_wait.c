#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rb_node {int dummy; } ;
struct intel_wait {struct rb_node node; int /*<<< orphan*/  tsk; } ;
struct intel_breadcrumbs {struct intel_wait* irq_wait; int /*<<< orphan*/  waiters; int /*<<< orphan*/  rb_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_3__ {int /*<<< orphan*/  seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (struct rb_node*) ; 
 int RB_EMPTY_NODE (struct rb_node*) ; 
 int /*<<< orphan*/  __intel_breadcrumbs_finish (struct intel_breadcrumbs*,TYPE_1__*) ; 
 int /*<<< orphan*/  __intel_breadcrumbs_next (struct intel_engine_cs*,struct rb_node*) ; 
 scalar_t__ chain_wakeup (struct rb_node*,int const) ; 
 scalar_t__ i915_seqno_passed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 TYPE_1__* to_wait (struct rb_node*) ; 
 int wakeup_priority (struct intel_breadcrumbs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_engine_remove_wait(struct intel_engine_cs *engine,
				       struct intel_wait *wait)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	lockdep_assert_held(&b->rb_lock);

	if (RB_EMPTY_NODE(&wait->node))
		goto out;

	if (b->irq_wait == wait) {
		const int priority = wakeup_priority(b, wait->tsk);
		struct rb_node *next;

		/* We are the current bottom-half. Find the next candidate,
		 * the first waiter in the queue on the remaining oldest
		 * request. As multiple seqnos may complete in the time it
		 * takes us to wake up and find the next waiter, we have to
		 * wake up that waiter for it to perform its own coherent
		 * completion check.
		 */
		next = rb_next(&wait->node);
		if (chain_wakeup(next, priority)) {
			/* If the next waiter is already complete,
			 * wake it up and continue onto the next waiter. So
			 * if have a small herd, they will wake up in parallel
			 * rather than sequentially, which should reduce
			 * the overall latency in waking all the completed
			 * clients.
			 *
			 * However, waking up a chain adds extra latency to
			 * the first_waiter. This is undesirable if that
			 * waiter is a high priority task.
			 */
			u32 seqno = intel_engine_get_seqno(engine);

			while (i915_seqno_passed(seqno, to_wait(next)->seqno)) {
				struct rb_node *n = rb_next(next);

				__intel_breadcrumbs_finish(b, to_wait(next));
				next = n;
				if (!chain_wakeup(next, priority))
					break;
			}
		}

		__intel_breadcrumbs_next(engine, next);
	} else {
		GEM_BUG_ON(rb_first(&b->waiters) == &wait->node);
	}

	GEM_BUG_ON(RB_EMPTY_NODE(&wait->node));
	rb_erase(&wait->node, &b->waiters);
	RB_CLEAR_NODE(&wait->node);

out:
	GEM_BUG_ON(b->irq_wait == wait);
	GEM_BUG_ON(rb_first(&b->waiters) !=
		   (b->irq_wait ? &b->irq_wait->node : NULL));
}