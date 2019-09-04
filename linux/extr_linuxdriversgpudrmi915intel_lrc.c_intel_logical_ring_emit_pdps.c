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
struct intel_engine_cs {int dummy; } ;
struct i915_request {struct intel_engine_cs* engine; TYPE_1__* gem_context; } ;
struct i915_hw_ppgtt {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct i915_hw_ppgtt* ppgtt; } ;

/* Variables and functions */
 int GEN8_3LVL_PDPES ; 
 int /*<<< orphan*/  GEN8_RING_PDP_LDW (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  GEN8_RING_PDP_UDW (struct intel_engine_cs*,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int const) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_page_dir_dma_addr (struct i915_hw_ppgtt*,int) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int const) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int intel_logical_ring_emit_pdps(struct i915_request *rq)
{
	struct i915_hw_ppgtt *ppgtt = rq->gem_context->ppgtt;
	struct intel_engine_cs *engine = rq->engine;
	const int num_lri_cmds = GEN8_3LVL_PDPES * 2;
	u32 *cs;
	int i;

	cs = intel_ring_begin(rq, num_lri_cmds * 2 + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(num_lri_cmds);
	for (i = GEN8_3LVL_PDPES - 1; i >= 0; i--) {
		const dma_addr_t pd_daddr = i915_page_dir_dma_addr(ppgtt, i);

		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_UDW(engine, i));
		*cs++ = upper_32_bits(pd_daddr);
		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_LDW(engine, i));
		*cs++ = lower_32_bits(pd_daddr);
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}