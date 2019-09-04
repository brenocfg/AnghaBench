#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_execlists {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {scalar_t__ context_size; scalar_t__ pinned_default_state; TYPE_1__ timeline; struct intel_engine_execlists execlists; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
struct i915_request {TYPE_4__* ring; int /*<<< orphan*/  postfix; int /*<<< orphan*/  gem_context; TYPE_3__* hw_context; TYPE_2__ fence; int /*<<< orphan*/  global_seqno; } ;
struct TYPE_10__ {int /*<<< orphan*/  head; int /*<<< orphan*/  vma; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lrc_reg_state; } ;

/* Variables and functions */
 int CTX_RING_BUFFER_START ; 
 int CTX_RING_HEAD ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LRC_STATE_PN ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __unwind_incomplete_requests (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  execlists_cancel_port_requests (struct intel_engine_execlists* const) ; 
 int /*<<< orphan*/  execlists_init_reg_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct intel_engine_cs*,TYPE_4__*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_ring_update_space (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_ring_wrap (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  reset_csb_pointers (struct intel_engine_execlists*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unwind_wa_tail (struct i915_request*) ; 

__attribute__((used)) static void execlists_reset(struct intel_engine_cs *engine,
			    struct i915_request *request)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	unsigned long flags;
	u32 *regs;

	GEM_TRACE("%s request global=%x, current=%d\n",
		  engine->name, request ? request->global_seqno : 0,
		  intel_engine_get_seqno(engine));

	spin_lock_irqsave(&engine->timeline.lock, flags);

	/*
	 * Catch up with any missed context-switch interrupts.
	 *
	 * Ideally we would just read the remaining CSB entries now that we
	 * know the gpu is idle. However, the CSB registers are sometimes^W
	 * often trashed across a GPU reset! Instead we have to rely on
	 * guessing the missed context-switch events by looking at what
	 * requests were completed.
	 */
	execlists_cancel_port_requests(execlists);

	/* Push back any incomplete requests for replay after the reset. */
	__unwind_incomplete_requests(engine);

	/* Following the reset, we need to reload the CSB read/write pointers */
	reset_csb_pointers(&engine->execlists);

	spin_unlock_irqrestore(&engine->timeline.lock, flags);

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
	if (!request || request->fence.error != -EIO)
		return;

	/*
	 * We want a simple context + ring to execute the breadcrumb update.
	 * We cannot rely on the context being intact across the GPU hang,
	 * so clear it and rebuild just what we need for the breadcrumb.
	 * All pending requests for this context will be zapped, and any
	 * future request will be after userspace has had the opportunity
	 * to recreate its own state.
	 */
	regs = request->hw_context->lrc_reg_state;
	if (engine->pinned_default_state) {
		memcpy(regs, /* skip restoring the vanilla PPHWSP */
		       engine->pinned_default_state + LRC_STATE_PN * PAGE_SIZE,
		       engine->context_size - PAGE_SIZE);
	}
	execlists_init_reg_state(regs,
				 request->gem_context, engine, request->ring);

	/* Move the RING_HEAD onto the breadcrumb, past the hanging batch */
	regs[CTX_RING_BUFFER_START + 1] = i915_ggtt_offset(request->ring->vma);

	request->ring->head = intel_ring_wrap(request->ring, request->postfix);
	regs[CTX_RING_HEAD + 1] = request->ring->head;

	intel_ring_update_space(request->ring);

	/* Reset WaIdleLiteRestore:bdw,skl as well */
	unwind_wa_tail(request);
}