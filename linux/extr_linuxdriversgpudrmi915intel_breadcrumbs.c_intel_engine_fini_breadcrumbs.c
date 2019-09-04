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
struct intel_breadcrumbs {int /*<<< orphan*/  signaler; int /*<<< orphan*/  signals; int /*<<< orphan*/  waiters; int /*<<< orphan*/  irq_wait; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_fake_irq (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void intel_engine_fini_breadcrumbs(struct intel_engine_cs *engine)
{
	struct intel_breadcrumbs *b = &engine->breadcrumbs;

	/* The engines should be idle and all requests accounted for! */
	WARN_ON(READ_ONCE(b->irq_wait));
	WARN_ON(!RB_EMPTY_ROOT(&b->waiters));
	WARN_ON(!list_empty(&b->signals));

	if (!IS_ERR_OR_NULL(b->signaler))
		kthread_stop(b->signaler);

	cancel_fake_irq(engine);
}