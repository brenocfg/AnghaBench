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
struct intel_engine_cs {int /*<<< orphan*/  scratch; } ;
struct i915_request {struct intel_engine_cs* engine; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int MI_SRM_LRM_GLOBAL_GTT ; 
 int MI_STORE_REGISTER_MEM ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RING_PP_DIR_BASE (struct intel_engine_cs const* const) ; 
 int /*<<< orphan*/  i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int flush_pd_dir(struct i915_request *rq)
{
	const struct intel_engine_cs * const engine = rq->engine;
	u32 *cs;

	cs = intel_ring_begin(rq, 4);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	/* Stall until the page table load is complete */
	*cs++ = MI_STORE_REGISTER_MEM | MI_SRM_LRM_GLOBAL_GTT;
	*cs++ = i915_mmio_reg_offset(RING_PP_DIR_BASE(engine));
	*cs++ = i915_ggtt_offset(engine->scratch);
	*cs++ = MI_NOOP;

	intel_ring_advance(rq, cs);
	return 0;
}