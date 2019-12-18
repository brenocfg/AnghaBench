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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct intel_engine_cs {TYPE_1__ active; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_2__ fence; struct intel_engine_cs* engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_request_submit (struct i915_request*) ; 
 int /*<<< orphan*/  dma_fence_set_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_mark_complete (struct i915_request*) ; 
 int /*<<< orphan*/  intel_engine_queue_breadcrumbs (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nop_submit_request(struct i915_request *request)
{
	struct intel_engine_cs *engine = request->engine;
	unsigned long flags;

	GEM_TRACE("%s fence %llx:%lld -> -EIO\n",
		  engine->name, request->fence.context, request->fence.seqno);
	dma_fence_set_error(&request->fence, -EIO);

	spin_lock_irqsave(&engine->active.lock, flags);
	__i915_request_submit(request);
	i915_request_mark_complete(request);
	spin_unlock_irqrestore(&engine->active.lock, flags);

	intel_engine_queue_breadcrumbs(engine);
}