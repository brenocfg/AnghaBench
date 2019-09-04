#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  lock; scalar_t__ seqno; } ;
struct intel_engine_cs {TYPE_3__ timeline; int /*<<< orphan*/  (* emit_breadcrumb ) (struct i915_request*,scalar_t__) ;int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {int global_seqno; int /*<<< orphan*/  execute; scalar_t__ postfix; TYPE_2__* ring; int /*<<< orphan*/  lock; TYPE_1__ fence; struct intel_engine_cs* engine; } ;
struct TYPE_6__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int i915_seqno_passed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_engine_enable_signaling (struct i915_request*,int) ; 
 int /*<<< orphan*/  intel_engine_get_seqno (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_to_timeline (struct i915_request*,TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i915_request*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timeline_get_seqno (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_i915_request_execute (struct i915_request*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void __i915_request_submit(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;
	u32 seqno;

	GEM_TRACE("%s fence %llx:%d -> global=%d, current %d\n",
		  engine->name,
		  request->fence.context, request->fence.seqno,
		  engine->timeline.seqno + 1,
		  intel_engine_get_seqno(engine));

	GEM_BUG_ON(!irqs_disabled());
	lockdep_assert_held(&engine->timeline.lock);

	GEM_BUG_ON(request->global_seqno);

	seqno = timeline_get_seqno(&engine->timeline);
	GEM_BUG_ON(!seqno);
	GEM_BUG_ON(i915_seqno_passed(intel_engine_get_seqno(engine), seqno));

	/* We may be recursing from the signal callback of another i915 fence */
	spin_lock_nested(&request->lock, SINGLE_DEPTH_NESTING);
	request->global_seqno = seqno;
	if (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &request->fence.flags))
		intel_engine_enable_signaling(request, false);
	spin_unlock(&request->lock);

	engine->emit_breadcrumb(request,
				request->ring->vaddr + request->postfix);

	/* Transfer from per-context onto the global per-engine timeline */
	move_to_timeline(request, &engine->timeline);

	trace_i915_request_execute(request);

	wake_up_all(&request->execute);
}