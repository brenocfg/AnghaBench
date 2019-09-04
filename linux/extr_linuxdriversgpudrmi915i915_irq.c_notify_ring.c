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
struct task_struct {int state; } ;
struct intel_wait {struct task_struct* tsk; scalar_t__ seqno; struct i915_request* request; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_lock; scalar_t__ irq_armed; int /*<<< orphan*/  irq_count; struct intel_wait* irq_wait; } ;
struct intel_engine_cs {TYPE_1__ breadcrumbs; int /*<<< orphan*/  irq_posted; scalar_t__ irq_seqno_barrier; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct i915_request {int /*<<< orphan*/  lock; TYPE_2__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 int /*<<< orphan*/  ENGINE_IRQ_BREADCRUMB ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int TASK_NORMAL ; 
 int /*<<< orphan*/  __intel_engine_disarm_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  dma_fence_signal_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  i915_request_completed (struct i915_request*) ; 
 struct i915_request* i915_request_get (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_put (struct i915_request*) ; 
 scalar_t__ i915_seqno_passed (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 scalar_t__ intel_wait_check_request (struct intel_wait*,struct i915_request*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_intel_engine_notify (struct intel_engine_cs*,struct intel_wait*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void notify_ring(struct intel_engine_cs *engine)
{
	const u32 seqno = intel_engine_get_seqno(engine);
	struct i915_request *rq = NULL;
	struct task_struct *tsk = NULL;
	struct intel_wait *wait;

	if (unlikely(!engine->breadcrumbs.irq_armed))
		return;

	rcu_read_lock();

	spin_lock(&engine->breadcrumbs.irq_lock);
	wait = engine->breadcrumbs.irq_wait;
	if (wait) {
		/*
		 * We use a callback from the dma-fence to submit
		 * requests after waiting on our own requests. To
		 * ensure minimum delay in queuing the next request to
		 * hardware, signal the fence now rather than wait for
		 * the signaler to be woken up. We still wake up the
		 * waiter in order to handle the irq-seqno coherency
		 * issues (we may receive the interrupt before the
		 * seqno is written, see __i915_request_irq_complete())
		 * and to handle coalescing of multiple seqno updates
		 * and many waiters.
		 */
		if (i915_seqno_passed(seqno, wait->seqno)) {
			struct i915_request *waiter = wait->request;

			if (waiter &&
			    !test_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				      &waiter->fence.flags) &&
			    intel_wait_check_request(wait, waiter))
				rq = i915_request_get(waiter);

			tsk = wait->tsk;
		} else {
			if (engine->irq_seqno_barrier &&
			    i915_seqno_passed(seqno, wait->seqno - 1)) {
				set_bit(ENGINE_IRQ_BREADCRUMB,
					&engine->irq_posted);
				tsk = wait->tsk;
			}
		}

		engine->breadcrumbs.irq_count++;
	} else {
		if (engine->breadcrumbs.irq_armed)
			__intel_engine_disarm_breadcrumbs(engine);
	}
	spin_unlock(&engine->breadcrumbs.irq_lock);

	if (rq) {
		spin_lock(&rq->lock);
		dma_fence_signal_locked(&rq->fence);
		GEM_BUG_ON(!i915_request_completed(rq));
		spin_unlock(&rq->lock);

		i915_request_put(rq);
	}

	if (tsk && tsk->state & TASK_NORMAL)
		wake_up_process(tsk);

	rcu_read_unlock();

	trace_intel_engine_notify(engine, wait);
}