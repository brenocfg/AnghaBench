#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_2__* engine; int /*<<< orphan*/  global_seqno; TYPE_3__ fence; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__ timeline; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_request_submit (struct i915_request*) ; 
 int /*<<< orphan*/  dma_fence_set_error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_engine_init_global_seqno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nop_complete_submit_request(struct i915_request *request)
{
	unsigned long flags;

	GEM_TRACE("%s fence %llx:%d -> -EIO\n",
		  request->engine->name,
		  request->fence.context, request->fence.seqno);
	dma_fence_set_error(&request->fence, -EIO);

	spin_lock_irqsave(&request->engine->timeline.lock, flags);
	__i915_request_submit(request);
	intel_engine_init_global_seqno(request->engine, request->global_seqno);
	spin_unlock_irqrestore(&request->engine->timeline.lock, flags);
}