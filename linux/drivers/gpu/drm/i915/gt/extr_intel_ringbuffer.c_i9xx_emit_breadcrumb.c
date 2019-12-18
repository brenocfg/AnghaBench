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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {scalar_t__ seqno; } ;
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; TYPE_3__ fence; TYPE_4__* timeline; TYPE_2__* engine; } ;
struct TYPE_8__ {scalar_t__ hwsp_ggtt; int /*<<< orphan*/  hwsp_offset; } ;
struct TYPE_5__ {scalar_t__ vma; } ;
struct TYPE_6__ {TYPE_1__ status_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ I915_GEM_HWS_SEQNO_ADDR ; 
 int /*<<< orphan*/  MI_FLUSH ; 
 scalar_t__ MI_NOOP ; 
 int /*<<< orphan*/  MI_STORE_DWORD_INDEX ; 
 scalar_t__ MI_USER_INTERRUPT ; 
 int /*<<< orphan*/  assert_ring_tail_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 
 scalar_t__ offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *i9xx_emit_breadcrumb(struct i915_request *rq, u32 *cs)
{
	GEM_BUG_ON(rq->timeline->hwsp_ggtt != rq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(rq->timeline->hwsp_offset) != I915_GEM_HWS_SEQNO_ADDR);

	*cs++ = MI_FLUSH;

	*cs++ = MI_STORE_DWORD_INDEX;
	*cs++ = I915_GEM_HWS_SEQNO_ADDR;
	*cs++ = rq->fence.seqno;

	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_NOOP;

	rq->tail = intel_ring_offset(rq, cs);
	assert_ring_tail_valid(rq->ring, rq->tail);

	return cs;
}