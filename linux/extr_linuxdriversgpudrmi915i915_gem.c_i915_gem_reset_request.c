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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  requests; } ;
struct intel_engine_cs {TYPE_1__ timeline; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {int /*<<< orphan*/  link; TYPE_2__ fence; int /*<<< orphan*/  gem_context; int /*<<< orphan*/  global_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_skip_context (struct i915_request*) ; 
 scalar_t__ i915_gem_context_is_banned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_mark_guilty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_context_mark_innocent (int /*<<< orphan*/ ) ; 
 struct i915_request* i915_gem_find_active_request (struct intel_engine_cs*) ; 
 scalar_t__ i915_request_completed (struct i915_request*) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  link ; 
 struct i915_request* list_prev_entry (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct i915_request *
i915_gem_reset_request(struct intel_engine_cs *engine,
		       struct i915_request *request,
		       bool stalled)
{
	/* The guilty request will get skipped on a hung engine.
	 *
	 * Users of client default contexts do not rely on logical
	 * state preserved between batches so it is safe to execute
	 * queued requests following the hang. Non default contexts
	 * rely on preserved state, so skipping a batch loses the
	 * evolution of the state and it needs to be considered corrupted.
	 * Executing more queued batches on top of corrupted state is
	 * risky. But we take the risk by trying to advance through
	 * the queued requests in order to make the client behaviour
	 * more predictable around resets, by not throwing away random
	 * amount of batches it has prepared for execution. Sophisticated
	 * clients can use gem_reset_stats_ioctl and dma fence status
	 * (exported via sync_file info ioctl on explicit fences) to observe
	 * when it loses the context state and should rebuild accordingly.
	 *
	 * The context ban, and ultimately the client ban, mechanism are safety
	 * valves if client submission ends up resulting in nothing more than
	 * subsequent hangs.
	 */

	if (i915_request_completed(request)) {
		GEM_TRACE("%s pardoned global=%d (fence %llx:%d), current %d\n",
			  engine->name, request->global_seqno,
			  request->fence.context, request->fence.seqno,
			  intel_engine_get_seqno(engine));
		stalled = false;
	}

	if (stalled) {
		i915_gem_context_mark_guilty(request->gem_context);
		i915_request_skip(request, -EIO);

		/* If this context is now banned, skip all pending requests. */
		if (i915_gem_context_is_banned(request->gem_context))
			engine_skip_context(request);
	} else {
		/*
		 * Since this is not the hung engine, it may have advanced
		 * since the hang declaration. Double check by refinding
		 * the active request at the time of the reset.
		 */
		request = i915_gem_find_active_request(engine);
		if (request) {
			unsigned long flags;

			i915_gem_context_mark_innocent(request->gem_context);
			dma_fence_set_error(&request->fence, -EAGAIN);

			/* Rewind the engine to replay the incomplete rq */
			spin_lock_irqsave(&engine->timeline.lock, flags);
			request = list_prev_entry(request, link);
			if (&request->link == &engine->timeline.requests)
				request = NULL;
			spin_unlock_irqrestore(&engine->timeline.lock, flags);
		}
	}

	return request;
}