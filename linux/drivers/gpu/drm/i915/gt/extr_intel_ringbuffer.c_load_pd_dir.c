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
struct intel_engine_cs {int /*<<< orphan*/  mmio_base; } ;
struct i915_request {struct intel_engine_cs* engine; } ;
struct i915_ppgtt {int /*<<< orphan*/  pd; } ;
struct TYPE_2__ {int ggtt_offset; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 void* MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  PP_DIR_DCLV_2G ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RING_PP_DIR_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PP_DIR_DCLV (int /*<<< orphan*/ ) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 TYPE_1__* px_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_pd_dir(struct i915_request *rq, const struct i915_ppgtt *ppgtt)
{
	const struct intel_engine_cs * const engine = rq->engine;
	u32 *cs;

	cs = intel_ring_begin(rq, 6);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_DIR_DCLV(engine->mmio_base));
	*cs++ = PP_DIR_DCLV_2G;

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(RING_PP_DIR_BASE(engine->mmio_base));
	*cs++ = px_base(ppgtt->pd)->ggtt_offset << 10;

	intel_ring_advance(rq, cs);

	return 0;
}