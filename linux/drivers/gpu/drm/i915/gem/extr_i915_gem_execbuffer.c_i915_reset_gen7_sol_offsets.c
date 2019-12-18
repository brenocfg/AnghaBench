#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {TYPE_1__* engine; int /*<<< orphan*/  i915; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GEN7_SO_WRITE_OFFSET (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_GEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 scalar_t__ MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ RCS0 ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int i915_reset_gen7_sol_offsets(struct i915_request *rq)
{
	u32 *cs;
	int i;

	if (!IS_GEN(rq->i915, 7) || rq->engine->id != RCS0) {
		DRM_DEBUG("sol reset is gen7/rcs only\n");
		return -EINVAL;
	}

	cs = intel_ring_begin(rq, 4 * 2 + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(4);
	for (i = 0; i < 4; i++) {
		*cs++ = i915_mmio_reg_offset(GEN7_SO_WRITE_OFFSET(i));
		*cs++ = 0;
	}
	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}