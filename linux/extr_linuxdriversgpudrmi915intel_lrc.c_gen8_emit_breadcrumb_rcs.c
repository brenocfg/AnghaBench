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
struct i915_request {int /*<<< orphan*/  tail; int /*<<< orphan*/  ring; int /*<<< orphan*/  engine; int /*<<< orphan*/  global_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int I915_GEM_HWS_INDEX ; 
 int MI_ARB_ENABLE ; 
 int MI_ARB_ON_OFF ; 
 int /*<<< orphan*/  MI_USER_INTERRUPT ; 
 int /*<<< orphan*/  assert_ring_tail_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gen8_emit_ggtt_write_rcs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_emit_wa_tail (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hws_seqno_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_offset (struct i915_request*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen8_emit_breadcrumb_rcs(struct i915_request *request, u32 *cs)
{
	/* We're using qword write, seqno should be aligned to 8 bytes. */
	BUILD_BUG_ON(I915_GEM_HWS_INDEX & 1);

	cs = gen8_emit_ggtt_write_rcs(cs, request->global_seqno,
				      intel_hws_seqno_address(request->engine));
	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	request->tail = intel_ring_offset(request, cs);
	assert_ring_tail_valid(request->ring, request->tail);

	gen8_emit_wa_tail(request, cs);
}