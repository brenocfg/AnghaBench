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
typedef  int u32 ;
struct intel_wait {int seqno; struct i915_request* request; int /*<<< orphan*/  tsk; } ;
struct intel_breadcrumbs {int /*<<< orphan*/  signaler; int /*<<< orphan*/  rb_lock; } ;
struct intel_engine_cs {struct intel_breadcrumbs breadcrumbs; } ;
struct TYPE_2__ {struct intel_wait wait; } ;
struct i915_request {int /*<<< orphan*/  lock; TYPE_1__ signaling; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int __intel_engine_add_wait (struct intel_engine_cs*,struct intel_wait*) ; 
 int i915_request_global_seqno (struct i915_request*) ; 
 int /*<<< orphan*/  insert_signal (struct intel_breadcrumbs*,struct i915_request*,int) ; 
 int /*<<< orphan*/  intel_wait_complete (struct intel_wait*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

bool intel_engine_enable_signaling(struct i915_request *request, bool wakeup)
{
	struct intel_engine_cs *engine = request->engine;
	struct intel_breadcrumbs *b = &engine->breadcrumbs;
	struct intel_wait *wait = &request->signaling.wait;
	u32 seqno;

	/*
	 * Note that we may be called from an interrupt handler on another
	 * device (e.g. nouveau signaling a fence completion causing us
	 * to submit a request, and so enable signaling). As such,
	 * we need to make sure that all other users of b->rb_lock protect
	 * against interrupts, i.e. use spin_lock_irqsave.
	 */

	/* locked by dma_fence_enable_sw_signaling() (irqsafe fence->lock) */
	GEM_BUG_ON(!irqs_disabled());
	lockdep_assert_held(&request->lock);

	seqno = i915_request_global_seqno(request);
	if (!seqno) /* will be enabled later upon execution */
		return true;

	GEM_BUG_ON(wait->seqno);
	wait->tsk = b->signaler;
	wait->request = request;
	wait->seqno = seqno;

	/*
	 * Add ourselves into the list of waiters, but registering our
	 * bottom-half as the signaller thread. As per usual, only the oldest
	 * waiter (not just signaller) is tasked as the bottom-half waking
	 * up all completed waiters after the user interrupt.
	 *
	 * If we are the oldest waiter, enable the irq (after which we
	 * must double check that the seqno did not complete).
	 */
	spin_lock(&b->rb_lock);
	insert_signal(b, request, seqno);
	wakeup &= __intel_engine_add_wait(engine, wait);
	spin_unlock(&b->rb_lock);

	if (wakeup) {
		wake_up_process(b->signaler);
		return !intel_wait_complete(wait);
	}

	return true;
}