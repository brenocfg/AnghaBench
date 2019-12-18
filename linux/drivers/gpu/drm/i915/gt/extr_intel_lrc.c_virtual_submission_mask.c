#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queue_priority_hint; } ;
struct TYPE_7__ {TYPE_2__ execlists; int /*<<< orphan*/  name; } ;
struct virtual_engine {TYPE_3__ base; TYPE_4__** siblings; int /*<<< orphan*/  request; } ;
struct TYPE_5__ {int /*<<< orphan*/  seqno; int /*<<< orphan*/  context; } ;
struct i915_request {TYPE_1__ fence; scalar_t__ execution_mask; } ;
typedef  scalar_t__ intel_engine_mask_t ;
struct TYPE_8__ {scalar_t__ mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct i915_request* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_request_skip (struct i915_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static intel_engine_mask_t virtual_submission_mask(struct virtual_engine *ve)
{
	struct i915_request *rq;
	intel_engine_mask_t mask;

	rq = READ_ONCE(ve->request);
	if (!rq)
		return 0;

	/* The rq is ready for submission; rq->execution_mask is now stable. */
	mask = rq->execution_mask;
	if (unlikely(!mask)) {
		/* Invalid selection, submit to a random engine in error */
		i915_request_skip(rq, -ENODEV);
		mask = ve->siblings[0]->mask;
	}

	GEM_TRACE("%s: rq=%llx:%lld, mask=%x, prio=%d\n",
		  ve->base.name,
		  rq->fence.context, rq->fence.seqno,
		  mask, ve->base.execlists.queue_priority_hint);

	return mask;
}