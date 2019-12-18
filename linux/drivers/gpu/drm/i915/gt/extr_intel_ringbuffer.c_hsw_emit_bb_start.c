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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 unsigned int I915_DISPATCH_SECURE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MI_BATCH_BUFFER_START ; 
 int MI_BATCH_NON_SECURE_HSW ; 
 int MI_BATCH_PPGTT_HSW ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int
hsw_emit_bb_start(struct i915_request *rq,
		  u64 offset, u32 len,
		  unsigned int dispatch_flags)
{
	u32 *cs;

	cs = intel_ring_begin(rq, 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_BATCH_BUFFER_START | (dispatch_flags & I915_DISPATCH_SECURE ?
		0 : MI_BATCH_PPGTT_HSW | MI_BATCH_NON_SECURE_HSW);
	/* bit0-7 is the length on GEN6+ */
	*cs++ = offset;
	intel_ring_advance(rq, cs);

	return 0;
}