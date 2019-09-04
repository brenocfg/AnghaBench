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
struct rb_node {int dummy; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  irq_lock; TYPE_1__* irq_wait; int /*<<< orphan*/  irq_armed; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_wait (struct rb_node*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __intel_breadcrumbs_next(struct intel_engine_cs *engine,
					    struct rb_node *next)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	spin_lock(&b->irq_lock);
	GEM_BUG_ON(!b->irq_armed);
	GEM_BUG_ON(!b->irq_wait);
	b->irq_wait = to_wait(next);
	spin_unlock(&b->irq_lock);

	/* We always wake up the next waiter that takes over as the bottom-half
	 * as we may delegate not only the irq-seqno barrier to the next waiter
	 * but also the task of waking up concurrent waiters.
	 */
	if (next)
		wake_up_process(to_wait(next)->tsk);
}