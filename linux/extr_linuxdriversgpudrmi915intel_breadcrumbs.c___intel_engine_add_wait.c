#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rb_node {struct rb_node* rb_left; struct rb_node* rb_right; } ;
struct intel_wait {scalar_t__ seqno; struct rb_node node; TYPE_1__* tsk; } ;
struct TYPE_5__ {struct rb_node* rb_node; } ;
struct intel_breadcrumbs {struct intel_wait* irq_wait; TYPE_2__ waiters; int /*<<< orphan*/  irq_armed; int /*<<< orphan*/  irq_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_4__ {scalar_t__ prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (struct rb_node*) ; 
 int __intel_breadcrumbs_enable_irq (struct intel_breadcrumbs*) ; 
 int /*<<< orphan*/  __intel_breadcrumbs_finish (struct intel_breadcrumbs*,struct intel_wait*) ; 
 int /*<<< orphan*/  __intel_breadcrumbs_next (struct intel_engine_cs*,struct rb_node*) ; 
 scalar_t__ i915_seqno_passed (scalar_t__,scalar_t__) ; 
 scalar_t__ intel_engine_get_seqno (struct intel_engine_cs*) ; 
 struct rb_node* rb_first (TYPE_2__*) ; 
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,TYPE_2__*) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 struct rb_node* rb_next (struct rb_node*) ; 
 struct rb_node* rb_prev (struct rb_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct intel_wait* to_wait (struct rb_node*) ; 

__attribute__((used)) static bool __intel_engine_add_wait(struct intel_engine_cs *engine,
				    struct intel_wait *wait)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	struct rb_node **p, *parent, *completed;
	bool first, armed;
	u32 seqno;

	GEM_BUG_ON(!wait->seqno);

	/* Insert the request into the retirement ordered list
	 * of waiters by walking the rbtree. If we are the oldest
	 * seqno in the tree (the first to be retired), then
	 * set ourselves as the bottom-half.
	 *
	 * As we descend the tree, prune completed branches since we hold the
	 * spinlock we know that the first_waiter must be delayed and can
	 * reduce some of the sequential wake up latency if we take action
	 * ourselves and wake up the completed tasks in parallel. Also, by
	 * removing stale elements in the tree, we may be able to reduce the
	 * ping-pong between the old bottom-half and ourselves as first-waiter.
	 */
	armed = false;
	first = true;
	parent = NULL;
	completed = NULL;
	seqno = intel_engine_get_seqno(engine);

	 /* If the request completed before we managed to grab the spinlock,
	  * return now before adding ourselves to the rbtree. We let the
	  * current bottom-half handle any pending wakeups and instead
	  * try and get out of the way quickly.
	  */
	if (i915_seqno_passed(seqno, wait->seqno)) {
		RB_CLEAR_NODE(&wait->node);
		return first;
	}

	p = &b->waiters.rb_node;
	while (*p) {
		parent = *p;
		if (wait->seqno == to_wait(parent)->seqno) {
			/* We have multiple waiters on the same seqno, select
			 * the highest priority task (that with the smallest
			 * task->prio) to serve as the bottom-half for this
			 * group.
			 */
			if (wait->tsk->prio > to_wait(parent)->tsk->prio) {
				p = &parent->rb_right;
				first = false;
			} else {
				p = &parent->rb_left;
			}
		} else if (i915_seqno_passed(wait->seqno,
					     to_wait(parent)->seqno)) {
			p = &parent->rb_right;
			if (i915_seqno_passed(seqno, to_wait(parent)->seqno))
				completed = parent;
			else
				first = false;
		} else {
			p = &parent->rb_left;
		}
	}
	rb_link_node(&wait->node, parent, p);
	rb_insert_color(&wait->node, &b->waiters);

	if (first) {
		spin_lock(&b->irq_lock);
		b->irq_wait = wait;
		/* After assigning ourselves as the new bottom-half, we must
		 * perform a cursory check to prevent a missed interrupt.
		 * Either we miss the interrupt whilst programming the hardware,
		 * or if there was a previous waiter (for a later seqno) they
		 * may be woken instead of us (due to the inherent race
		 * in the unlocked read of b->irq_seqno_bh in the irq handler)
		 * and so we miss the wake up.
		 */
		armed = __intel_breadcrumbs_enable_irq(b);
		spin_unlock(&b->irq_lock);
	}

	if (completed) {
		/* Advance the bottom-half (b->irq_wait) before we wake up
		 * the waiters who may scribble over their intel_wait
		 * just as the interrupt handler is dereferencing it via
		 * b->irq_wait.
		 */
		if (!first) {
			struct rb_node *next = rb_next(completed);
			GEM_BUG_ON(next == &wait->node);
			__intel_breadcrumbs_next(engine, next);
		}

		do {
			struct intel_wait *crumb = to_wait(completed);
			completed = rb_prev(completed);
			__intel_breadcrumbs_finish(b, crumb);
		} while (completed);
	}

	GEM_BUG_ON(!b->irq_wait);
	GEM_BUG_ON(!b->irq_armed);
	GEM_BUG_ON(rb_first(&b->waiters) != &b->irq_wait->node);

	return armed;
}