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
struct intel_engine_cs {int dummy; } ;
struct i915_request {struct intel_engine_cs* engine; } ;
struct TYPE_3__ {int ggtt_offset; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct i915_hw_ppgtt {TYPE_2__ pd; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 void* MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  PP_DIR_DCLV_2G ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RING_PP_DIR_BASE (struct intel_engine_cs const* const) ; 
 int /*<<< orphan*/  RING_PP_DIR_DCLV (struct intel_engine_cs const* const) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int load_pd_dir(struct i915_request *rq,
		       const struct i915_hw_ppgtt *ppgtt)
{
	const struct intel_engine_cs * const engine = rq->engine;
	u32 *cs;

	cs = intel_ring_begin(rq, 6);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_DIR_DCLV(engine));
	*cs++ = PP_DIR_DCLV_2G;

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_DIR_BASE(engine));
	*cs++ = ppgtt->pd.base.ggtt_offset << 10;

	intel_ring_advance(rq, cs);

	return 0;
}