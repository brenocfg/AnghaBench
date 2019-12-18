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
 int BIT (int) ; 
 unsigned int const I915_DISPATCH_SECURE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MI_ARB_DISABLE ; 
 int MI_ARB_ON_OFF ; 
 int MI_BATCH_BUFFER_START_GEN8 ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen8_emit_bb_start(struct i915_request *rq,
			      u64 offset, u32 len,
			      const unsigned int flags)
{
	u32 *cs;

	cs = intel_ring_begin(rq, 4);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	/*
	 * WaDisableCtxRestoreArbitration:bdw,chv
	 *
	 * We don't need to perform MI_ARB_ENABLE as often as we do (in
	 * particular all the gen that do not need the w/a at all!), if we
	 * took care to make sure that on every switch into this context
	 * (both ordinary and for preemption) that arbitrartion was enabled
	 * we would be fine.  However, for gen8 there is another w/a that
	 * requires us to not preempt inside GPGPU execution, so we keep
	 * arbitration disabled for gen8 batches. Arbitration will be
	 * re-enabled before we close the request
	 * (engine->emit_fini_breadcrumb).
	 */
	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	/* FIXME(BDW+): Address space and security selectors. */
	*cs++ = MI_BATCH_BUFFER_START_GEN8 |
		(flags & I915_DISPATCH_SECURE ? 0 : BIT(8));
	*cs++ = lower_32_bits(offset);
	*cs++ = upper_32_bits(offset);

	intel_ring_advance(rq, cs);

	return 0;
}