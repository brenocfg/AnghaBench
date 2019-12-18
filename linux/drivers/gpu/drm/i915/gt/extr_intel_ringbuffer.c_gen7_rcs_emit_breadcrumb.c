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
struct TYPE_4__ {int /*<<< orphan*/  seqno; } ;
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; TYPE_2__ fence; TYPE_1__* timeline; } ;
struct TYPE_3__ {int /*<<< orphan*/  hwsp_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_OP_PIPE_CONTROL (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int /*<<< orphan*/  MI_USER_INTERRUPT ; 
 int PIPE_CONTROL_CS_STALL ; 
 int PIPE_CONTROL_DC_FLUSH_ENABLE ; 
 int PIPE_CONTROL_DEPTH_CACHE_FLUSH ; 
 int PIPE_CONTROL_FLUSH_ENABLE ; 
 int PIPE_CONTROL_GLOBAL_GTT_IVB ; 
 int PIPE_CONTROL_QW_WRITE ; 
 int PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH ; 
 int /*<<< orphan*/  assert_ring_tail_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 *gen7_rcs_emit_breadcrumb(struct i915_request *rq, u32 *cs)
{
	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = (PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
		 PIPE_CONTROL_DEPTH_CACHE_FLUSH |
		 PIPE_CONTROL_DC_FLUSH_ENABLE |
		 PIPE_CONTROL_FLUSH_ENABLE |
		 PIPE_CONTROL_QW_WRITE |
		 PIPE_CONTROL_GLOBAL_GTT_IVB |
		 PIPE_CONTROL_CS_STALL);
	*cs++ = rq->timeline->hwsp_offset;
	*cs++ = rq->fence.seqno;

	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_NOOP;

	rq->tail = intel_ring_offset(rq, cs);
	assert_ring_tail_valid(rq->ring, rq->tail);

	return cs;
}