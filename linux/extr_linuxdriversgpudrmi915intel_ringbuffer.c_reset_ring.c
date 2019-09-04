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
struct intel_engine_cs {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
struct i915_request {TYPE_1__ fence; int /*<<< orphan*/  head; TYPE_2__* ring; int /*<<< orphan*/  global_seqno; } ;
struct TYPE_4__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_wrap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_request (struct i915_request*) ; 

__attribute__((used)) static void reset_ring(struct intel_engine_cs *engine, struct i915_request *rq)
{
	GEM_TRACE("%s seqno=%x\n", engine->name, rq ? rq->global_seqno : 0);

	/*
	 * Try to restore the logical GPU state to match the continuation
	 * of the request queue. If we skip the context/PD restore, then
	 * the next request may try to execute assuming that its context
	 * is valid and loaded on the GPU and so may try to access invalid
	 * memory, prompting repeated GPU hangs.
	 *
	 * If the request was guilty, we still restore the logical state
	 * in case the next request requires it (e.g. the aliasing ppgtt),
	 * but skip over the hung batch.
	 *
	 * If the request was innocent, we try to replay the request with
	 * the restored context.
	 */
	if (rq) {
		/* If the rq hung, jump to its breadcrumb and skip the batch */
		rq->ring->head = intel_ring_wrap(rq->ring, rq->head);
		if (rq->fence.error == -EIO)
			skip_request(rq);
	}
}