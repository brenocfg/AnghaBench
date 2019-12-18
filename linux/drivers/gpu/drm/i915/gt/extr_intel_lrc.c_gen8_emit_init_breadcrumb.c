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
struct TYPE_3__ {int seqno; } ;
struct i915_request {int /*<<< orphan*/  infix; TYPE_1__ fence; TYPE_2__* timeline; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwsp_offset; int /*<<< orphan*/  has_initial_breadcrumb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_ARB_CHECK ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int MI_STORE_DWORD_IMM_GEN4 ; 
 int MI_USE_GGTT ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gen8_emit_init_breadcrumb(struct i915_request *rq)
{
	u32 *cs;

	GEM_BUG_ON(!rq->timeline->has_initial_breadcrumb);

	cs = intel_ring_begin(rq, 6);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	/*
	 * Check if we have been preempted before we even get started.
	 *
	 * After this point i915_request_started() reports true, even if
	 * we get preempted and so are no longer running.
	 */
	*cs++ = MI_ARB_CHECK;
	*cs++ = MI_NOOP;

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = rq->timeline->hwsp_offset;
	*cs++ = 0;
	*cs++ = rq->fence.seqno - 1;

	intel_ring_advance(rq, cs);

	/* Record the updated position of the request's payload */
	rq->infix = intel_ring_offset(rq, cs);

	return 0;
}