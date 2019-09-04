#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; int /*<<< orphan*/  global_seqno; } ;

/* Variables and functions */
 int I915_GEM_HWS_INDEX ; 
 int /*<<< orphan*/  MI_STORE_DWORD_INDEX ; 
 int MI_STORE_DWORD_INDEX_SHIFT ; 
 int /*<<< orphan*/  MI_USER_INTERRUPT ; 
 int /*<<< orphan*/  assert_ring_tail_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i9xx_emit_breadcrumb(struct i915_request *rq, u32 *cs)
{
	*cs++ = MI_STORE_DWORD_INDEX;
	*cs++ = I915_GEM_HWS_INDEX << MI_STORE_DWORD_INDEX_SHIFT;
	*cs++ = rq->global_seqno;
	*cs++ = MI_USER_INTERRUPT;

	rq->tail = intel_ring_offset(rq, cs);
	assert_ring_tail_valid(rq->ring, rq->tail);
}