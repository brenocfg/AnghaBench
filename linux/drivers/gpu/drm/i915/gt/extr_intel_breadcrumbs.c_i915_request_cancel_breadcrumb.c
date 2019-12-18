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
struct intel_context {int /*<<< orphan*/  signal_link; int /*<<< orphan*/  signals; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  irq_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct i915_request {TYPE_1__ fence; int /*<<< orphan*/  signal_link; struct intel_context* hw_context; int /*<<< orphan*/  lock; TYPE_2__* engine; } ;
struct TYPE_4__ {struct intel_breadcrumbs breadcrumbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_FENCE_FLAG_SIGNAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i915_request_cancel_breadcrumb(struct i915_request *rq)
{
	struct intel_breadcrumbs *b = &rq->engine->breadcrumbs;

	lockdep_assert_held(&rq->lock);
	lockdep_assert_irqs_disabled();

	/*
	 * We must wait for b->irq_lock so that we know the interrupt handler
	 * has released its reference to the intel_context and has completed
	 * the DMA_FENCE_FLAG_SIGNALED_BIT/I915_FENCE_FLAG_SIGNAL dance (if
	 * required).
	 */
	spin_lock(&b->irq_lock);
	if (test_bit(I915_FENCE_FLAG_SIGNAL, &rq->fence.flags)) {
		struct intel_context *ce = rq->hw_context;

		list_del(&rq->signal_link);
		if (list_empty(&ce->signals))
			list_del_init(&ce->signal_link);

		clear_bit(I915_FENCE_FLAG_SIGNAL, &rq->fence.flags);
	}
	spin_unlock(&b->irq_lock);
}