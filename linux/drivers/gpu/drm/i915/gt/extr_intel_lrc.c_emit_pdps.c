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
struct intel_engine_cs {int (* emit_flush ) (struct i915_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mmio_base; } ;
struct i915_request {int /*<<< orphan*/  i915; TYPE_1__* hw_context; struct intel_engine_cs* engine; } ;
struct i915_ppgtt {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_FLUSH ; 
 int /*<<< orphan*/  EMIT_INVALIDATE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int GEN8_3LVL_PDPES ; 
 int /*<<< orphan*/  GEN8_RING_PDP_LDW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GEN8_RING_PDP_UDW (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MI_LOAD_REGISTER_IMM (int) ; 
 int MI_LRI_FORCE_POSTED ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_page_dir_dma_addr (struct i915_ppgtt* const,int) ; 
 struct i915_ppgtt* i915_vm_to_ppgtt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intel_ring_begin (struct i915_request*,int) ; 
 int /*<<< orphan*/  intel_vgpu_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/  const) ; 
 int stub1 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub2 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub3 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int stub4 (struct i915_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int emit_pdps(struct i915_request *rq)
{
	const struct intel_engine_cs * const engine = rq->engine;
	struct i915_ppgtt * const ppgtt = i915_vm_to_ppgtt(rq->hw_context->vm);
	int err, i;
	u32 *cs;

	GEM_BUG_ON(intel_vgpu_active(rq->i915));

	/*
	 * Beware ye of the dragons, this sequence is magic!
	 *
	 * Small changes to this sequence can cause anything from
	 * GPU hangs to forcewake errors and machine lockups!
	 */

	/* Flush any residual operations from the context load */
	err = engine->emit_flush(rq, EMIT_FLUSH);
	if (err)
		return err;

	/* Magic required to prevent forcewake errors! */
	err = engine->emit_flush(rq, EMIT_INVALIDATE);
	if (err)
		return err;

	cs = intel_ring_begin(rq, 4 * GEN8_3LVL_PDPES + 2);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	/* Ensure the LRI have landed before we invalidate & continue */
	*cs++ = MI_LOAD_REGISTER_IMM(2 * GEN8_3LVL_PDPES) | MI_LRI_FORCE_POSTED;
	for (i = GEN8_3LVL_PDPES; i--; ) {
		const dma_addr_t pd_daddr = i915_page_dir_dma_addr(ppgtt, i);
		u32 base = engine->mmio_base;

		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_UDW(base, i));
		*cs++ = upper_32_bits(pd_daddr);
		*cs++ = i915_mmio_reg_offset(GEN8_RING_PDP_LDW(base, i));
		*cs++ = lower_32_bits(pd_daddr);
	}
	*cs++ = MI_NOOP;

	intel_ring_advance(rq, cs);

	/* Be doubly sure the LRI have landed before proceeding */
	err = engine->emit_flush(rq, EMIT_FLUSH);
	if (err)
		return err;

	/* Re-invalidate the TLB for luck */
	return engine->emit_flush(rq, EMIT_INVALIDATE);
}