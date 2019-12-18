#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_execlists {int dummy; } ;
struct intel_engine_cs {int /*<<< orphan*/  name; scalar_t__ context_size; scalar_t__ pinned_default_state; struct intel_engine_execlists execlists; } ;
struct intel_context {TYPE_1__* ring; int /*<<< orphan*/ * lrc_reg_state; int /*<<< orphan*/  state; int /*<<< orphan*/  active; } ;
struct i915_request {int /*<<< orphan*/  head; struct intel_context* hw_context; } ;
struct TYPE_4__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __execlists_update_reg_state (struct intel_context*,struct intel_engine_cs*) ; 
 int /*<<< orphan*/  __i915_request_reset (struct i915_request*,int) ; 
 int /*<<< orphan*/  __unwind_incomplete_requests (struct intel_engine_cs*) ; 
 struct i915_request* active_request (struct i915_request*) ; 
 int /*<<< orphan*/  cancel_port_requests (struct intel_engine_execlists* const) ; 
 struct i915_request* execlists_active (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  execlists_init_reg_state (int /*<<< orphan*/ *,struct intel_context*,struct intel_engine_cs*,TYPE_1__*) ; 
 int i915_active_is_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_request_started (struct i915_request*) ; 
 int /*<<< orphan*/  i915_vma_is_pinned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_update_space (TYPE_1__*) ; 
 int /*<<< orphan*/  intel_ring_wrap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  process_csb (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  reset_csb_pointers (struct intel_engine_cs*) ; 

__attribute__((used)) static void __execlists_reset(struct intel_engine_cs *engine, bool stalled)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	struct intel_context *ce;
	struct i915_request *rq;
	u32 *regs;

	process_csb(engine); /* drain preemption events */

	/* Following the reset, we need to reload the CSB read/write pointers */
	reset_csb_pointers(engine);

	/*
	 * Save the currently executing context, even if we completed
	 * its request, it was still running at the time of the
	 * reset and will have been clobbered.
	 */
	rq = execlists_active(execlists);
	if (!rq)
		goto unwind;

	ce = rq->hw_context;
	GEM_BUG_ON(i915_active_is_idle(&ce->active));
	GEM_BUG_ON(!i915_vma_is_pinned(ce->state));
	rq = active_request(rq);
	if (!rq) {
		ce->ring->head = ce->ring->tail;
		goto out_replay;
	}

	ce->ring->head = intel_ring_wrap(ce->ring, rq->head);

	/*
	 * If this request hasn't started yet, e.g. it is waiting on a
	 * semaphore, we need to avoid skipping the request or else we
	 * break the signaling chain. However, if the context is corrupt
	 * the request will not restart and we will be stuck with a wedged
	 * device. It is quite often the case that if we issue a reset
	 * while the GPU is loading the context image, that the context
	 * image becomes corrupt.
	 *
	 * Otherwise, if we have not started yet, the request should replay
	 * perfectly and we do not need to flag the result as being erroneous.
	 */
	if (!i915_request_started(rq))
		goto out_replay;

	/*
	 * If the request was innocent, we leave the request in the ELSP
	 * and will try to replay it on restarting. The context image may
	 * have been corrupted by the reset, in which case we may have
	 * to service a new GPU hang, but more likely we can continue on
	 * without impact.
	 *
	 * If the request was guilty, we presume the context is corrupt
	 * and have to at least restore the RING register in the context
	 * image back to the expected values to skip over the guilty request.
	 */
	__i915_request_reset(rq, stalled);
	if (!stalled)
		goto out_replay;

	/*
	 * We want a simple context + ring to execute the breadcrumb update.
	 * We cannot rely on the context being intact across the GPU hang,
	 * so clear it and rebuild just what we need for the breadcrumb.
	 * All pending requests for this context will be zapped, and any
	 * future request will be after userspace has had the opportunity
	 * to recreate its own state.
	 */
	regs = ce->lrc_reg_state;
	if (engine->pinned_default_state) {
		memcpy(regs, /* skip restoring the vanilla PPHWSP */
		       engine->pinned_default_state + LRC_STATE_PN * PAGE_SIZE,
		       engine->context_size - PAGE_SIZE);
	}
	execlists_init_reg_state(regs, ce, engine, ce->ring);

out_replay:
	GEM_TRACE("%s replay {head:%04x, tail:%04x\n",
		  engine->name, ce->ring->head, ce->ring->tail);
	intel_ring_update_space(ce->ring);
	__execlists_update_reg_state(ce, engine);

unwind:
	/* Push back any incomplete requests for replay after the reset. */
	cancel_port_requests(execlists);
	__unwind_incomplete_requests(engine);
}