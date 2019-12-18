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
struct i915_request {TYPE_2__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** remap_info; } ;
struct TYPE_4__ {TYPE_1__ l3_parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN7_L3LOG (int,int) ; 
 int GEN7_L3LOG_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int remap_l3_slice(struct i915_request *rq, int slice)
{
	u32 *cs, *remap_info = rq->i915->l3_parity.remap_info[slice];
	int i;

	if (!remap_info)
		return 0;

	cs = intel_ring_begin(rq, GEN7_L3LOG_SIZE/4 * 2 + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	/*
	 * Note: We do not worry about the concurrent register cacheline hang
	 * here because no other code should access these registers other than
	 * at initialization time.
	 */
	*cs++ = MI_LOAD_REGISTER_IMM(GEN7_L3LOG_SIZE/4);
	for (i = 0; i < GEN7_L3LOG_SIZE/4; i++) {
		*cs++ = i915_mmio_reg_offset(GEN7_L3LOG(slice, i));
		*cs++ = remap_info[i];
	}
	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}