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
typedef  int /*<<< orphan*/  u32 ;
struct intel_breadcrumbs {int /*<<< orphan*/  irq_lock; TYPE_2__* irq_wait; } ;
struct intel_engine_cs {int /*<<< orphan*/  (* irq_seqno_barrier ) (struct intel_engine_cs*) ;struct intel_breadcrumbs breadcrumbs; int /*<<< orphan*/  irq_posted; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct i915_request {TYPE_1__ fence; struct intel_engine_cs* engine; } ;
struct TYPE_4__ {scalar_t__ tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int /*<<< orphan*/  ENGINE_IRQ_BREADCRUMB ; 
 scalar_t__ __i915_request_completed (struct i915_request const*,int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  i915_request_global_seqno (struct i915_request const*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_engine_cs*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static inline bool
__i915_request_irq_complete(const struct i915_request *rq)
{
	struct intel_engine_cs *engine = rq->engine;
	u32 seqno;

	/* Note that the engine may have wrapped around the seqno, and
	 * so our request->global_seqno will be ahead of the hardware,
	 * even though it completed the request before wrapping. We catch
	 * this by kicking all the waiters before resetting the seqno
	 * in hardware, and also signal the fence.
	 */
	if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags))
		return true;

	/* The request was dequeued before we were awoken. We check after
	 * inspecting the hw to confirm that this was the same request
	 * that generated the HWS update. The memory barriers within
	 * the request execution are sufficient to ensure that a check
	 * after reading the value from hw matches this request.
	 */
	seqno = i915_request_global_seqno(rq);
	if (!seqno)
		return false;

	/* Before we do the heavier coherent read of the seqno,
	 * check the value (hopefully) in the CPU cacheline.
	 */
	if (__i915_request_completed(rq, seqno))
		return true;

	/* Ensure our read of the seqno is coherent so that we
	 * do not "miss an interrupt" (i.e. if this is the last
	 * request and the seqno write from the GPU is not visible
	 * by the time the interrupt fires, we will see that the
	 * request is incomplete and go back to sleep awaiting
	 * another interrupt that will never come.)
	 *
	 * Strictly, we only need to do this once after an interrupt,
	 * but it is easier and safer to do it every time the waiter
	 * is woken.
	 */
	if (engine->irq_seqno_barrier &&
	    test_and_clear_bit(ENGINE_IRQ_BREADCRUMB, &engine->irq_posted)) {
		struct intel_breadcrumbs *b = &engine->breadcrumbs;

		/* The ordering of irq_posted versus applying the barrier
		 * is crucial. The clearing of the current irq_posted must
		 * be visible before we perform the barrier operation,
		 * such that if a subsequent interrupt arrives, irq_posted
		 * is reasserted and our task rewoken (which causes us to
		 * do another __i915_request_irq_complete() immediately
		 * and reapply the barrier). Conversely, if the clear
		 * occurs after the barrier, then an interrupt that arrived
		 * whilst we waited on the barrier would not trigger a
		 * barrier on the next pass, and the read may not see the
		 * seqno update.
		 */
		engine->irq_seqno_barrier(engine);

		/* If we consume the irq, but we are no longer the bottom-half,
		 * the real bottom-half may not have serialised their own
		 * seqno check with the irq-barrier (i.e. may have inspected
		 * the seqno before we believe it coherent since they see
		 * irq_posted == false but we are still running).
		 */
		spin_lock_irq(&b->irq_lock);
		if (b->irq_wait && b->irq_wait->tsk != current)
			/* Note that if the bottom-half is changed as we
			 * are sending the wake-up, the new bottom-half will
			 * be woken by whomever made the change. We only have
			 * to worry about when we steal the irq-posted for
			 * ourself.
			 */
			wake_up_process(b->irq_wait->tsk);
		spin_unlock_irq(&b->irq_lock);

		if (__i915_request_completed(rq, seqno))
			return true;
	}

	return false;
}