#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_ring {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {int offset; scalar_t__ size; } ;
struct TYPE_5__ {int size; int offset; } ;
struct i915_ctx_workarounds {TYPE_3__ per_ctx; int /*<<< orphan*/  vma; TYPE_2__ indirect_ctx; } ;
struct intel_engine_cs {int mmio_base; scalar_t__ class; struct i915_ctx_workarounds wa_ctx; struct drm_i915_private* i915; } ;
struct i915_hw_ppgtt {int /*<<< orphan*/  vm; } ;
struct i915_gem_context {int /*<<< orphan*/  ppgtt; } ;
struct TYPE_4__ {struct i915_hw_ppgtt* aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_CTX_PML4 (struct i915_hw_ppgtt*,int*) ; 
 int CACHELINE_BYTES ; 
 int CTX_BB_HEAD_L ; 
 int CTX_BB_HEAD_U ; 
 int CTX_BB_PER_CTX_PTR ; 
 int CTX_BB_STATE ; 
 int CTX_CONTEXT_CONTROL ; 
 int CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT ; 
 int CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT ; 
 int CTX_CTRL_INHIBIT_SYN_CTX_SWITCH ; 
 int CTX_CTRL_RS_CTX_ENABLE ; 
 int CTX_CTX_TIMESTAMP ; 
 size_t CTX_LRI_HEADER_0 ; 
 size_t CTX_LRI_HEADER_1 ; 
 size_t CTX_LRI_HEADER_2 ; 
 int CTX_PDP0_LDW ; 
 int CTX_PDP0_UDW ; 
 int CTX_PDP1_LDW ; 
 int CTX_PDP1_UDW ; 
 int CTX_PDP2_LDW ; 
 int CTX_PDP2_UDW ; 
 int CTX_PDP3_LDW ; 
 int CTX_PDP3_UDW ; 
 int CTX_RCS_INDIRECT_CTX ; 
 int CTX_RCS_INDIRECT_CTX_OFFSET ; 
 int /*<<< orphan*/  CTX_REG (int*,int,int /*<<< orphan*/ ,int) ; 
 int CTX_RING_BUFFER_CONTROL ; 
 int CTX_RING_BUFFER_START ; 
 int CTX_RING_HEAD ; 
 int CTX_RING_TAIL ; 
 int CTX_R_PWR_CLK_STATE ; 
 int CTX_SECOND_BB_HEAD_L ; 
 int CTX_SECOND_BB_HEAD_U ; 
 int CTX_SECOND_BB_STATE ; 
 int /*<<< orphan*/  GEN8_RING_PDP_LDW (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  GEN8_RING_PDP_UDW (struct intel_engine_cs*,int) ; 
 int /*<<< orphan*/  GEN8_R_PWR_CLK_STATE ; 
 scalar_t__ HAS_RESOURCE_STREAMER (struct drm_i915_private*) ; 
 int MI_LOAD_REGISTER_IMM (int) ; 
 int MI_LRI_FORCE_POSTED ; 
 scalar_t__ RENDER_CLASS ; 
 int /*<<< orphan*/  RING_BBADDR (int) ; 
 int /*<<< orphan*/  RING_BBADDR_UDW (int) ; 
 int /*<<< orphan*/  RING_BBSTATE (int) ; 
 int /*<<< orphan*/  RING_BB_PER_CTX_PTR (int) ; 
 int RING_BB_PPGTT ; 
 int /*<<< orphan*/  RING_CONTEXT_CONTROL (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  RING_CTL (int) ; 
 int RING_CTL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_CTX_TIMESTAMP (int) ; 
 int /*<<< orphan*/  RING_HEAD (int) ; 
 int /*<<< orphan*/  RING_INDIRECT_CTX (int) ; 
 int /*<<< orphan*/  RING_INDIRECT_CTX_OFFSET (int) ; 
 int /*<<< orphan*/  RING_SBBADDR (int) ; 
 int /*<<< orphan*/  RING_SBBADDR_UDW (int) ; 
 int /*<<< orphan*/  RING_SBBSTATE (int) ; 
 int /*<<< orphan*/  RING_START (int) ; 
 int /*<<< orphan*/  RING_TAIL (int) ; 
 int RING_VALID ; 
 int _MASKED_BIT_DISABLE (int) ; 
 int _MASKED_BIT_ENABLE (int) ; 
 int i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_oa_init_reg_state (struct intel_engine_cs*,struct i915_gem_context*,int*) ; 
 scalar_t__ i915_vm_is_48bit (int /*<<< orphan*/ *) ; 
 int intel_lr_indirect_ctx_offset (struct intel_engine_cs*) ; 
 int make_rpcs (struct drm_i915_private*) ; 

__attribute__((used)) static void execlists_init_reg_state(u32 *regs,
				     struct i915_gem_context *ctx,
				     struct intel_engine_cs *engine,
				     struct intel_ring *ring)
{
	struct drm_i915_private *dev_priv = engine->i915;
	struct i915_hw_ppgtt *ppgtt = ctx->ppgtt ?: dev_priv->mm.aliasing_ppgtt;
	u32 base = engine->mmio_base;
	bool rcs = engine->class == RENDER_CLASS;

	/* A context is actually a big batch buffer with several
	 * MI_LOAD_REGISTER_IMM commands followed by (reg, value) pairs. The
	 * values we are setting here are only for the first context restore:
	 * on a subsequent save, the GPU will recreate this batchbuffer with new
	 * values (including all the missing MI_LOAD_REGISTER_IMM commands that
	 * we are not initializing here).
	 */
	regs[CTX_LRI_HEADER_0] = MI_LOAD_REGISTER_IMM(rcs ? 14 : 11) |
				 MI_LRI_FORCE_POSTED;

	CTX_REG(regs, CTX_CONTEXT_CONTROL, RING_CONTEXT_CONTROL(engine),
		_MASKED_BIT_DISABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT |
				    CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT) |
		_MASKED_BIT_ENABLE(CTX_CTRL_INHIBIT_SYN_CTX_SWITCH |
				   (HAS_RESOURCE_STREAMER(dev_priv) ?
				   CTX_CTRL_RS_CTX_ENABLE : 0)));
	CTX_REG(regs, CTX_RING_HEAD, RING_HEAD(base), 0);
	CTX_REG(regs, CTX_RING_TAIL, RING_TAIL(base), 0);
	CTX_REG(regs, CTX_RING_BUFFER_START, RING_START(base), 0);
	CTX_REG(regs, CTX_RING_BUFFER_CONTROL, RING_CTL(base),
		RING_CTL_SIZE(ring->size) | RING_VALID);
	CTX_REG(regs, CTX_BB_HEAD_U, RING_BBADDR_UDW(base), 0);
	CTX_REG(regs, CTX_BB_HEAD_L, RING_BBADDR(base), 0);
	CTX_REG(regs, CTX_BB_STATE, RING_BBSTATE(base), RING_BB_PPGTT);
	CTX_REG(regs, CTX_SECOND_BB_HEAD_U, RING_SBBADDR_UDW(base), 0);
	CTX_REG(regs, CTX_SECOND_BB_HEAD_L, RING_SBBADDR(base), 0);
	CTX_REG(regs, CTX_SECOND_BB_STATE, RING_SBBSTATE(base), 0);
	if (rcs) {
		struct i915_ctx_workarounds *wa_ctx = &engine->wa_ctx;

		CTX_REG(regs, CTX_RCS_INDIRECT_CTX, RING_INDIRECT_CTX(base), 0);
		CTX_REG(regs, CTX_RCS_INDIRECT_CTX_OFFSET,
			RING_INDIRECT_CTX_OFFSET(base), 0);
		if (wa_ctx->indirect_ctx.size) {
			u32 ggtt_offset = i915_ggtt_offset(wa_ctx->vma);

			regs[CTX_RCS_INDIRECT_CTX + 1] =
				(ggtt_offset + wa_ctx->indirect_ctx.offset) |
				(wa_ctx->indirect_ctx.size / CACHELINE_BYTES);

			regs[CTX_RCS_INDIRECT_CTX_OFFSET + 1] =
				intel_lr_indirect_ctx_offset(engine) << 6;
		}

		CTX_REG(regs, CTX_BB_PER_CTX_PTR, RING_BB_PER_CTX_PTR(base), 0);
		if (wa_ctx->per_ctx.size) {
			u32 ggtt_offset = i915_ggtt_offset(wa_ctx->vma);

			regs[CTX_BB_PER_CTX_PTR + 1] =
				(ggtt_offset + wa_ctx->per_ctx.offset) | 0x01;
		}
	}

	regs[CTX_LRI_HEADER_1] = MI_LOAD_REGISTER_IMM(9) | MI_LRI_FORCE_POSTED;

	CTX_REG(regs, CTX_CTX_TIMESTAMP, RING_CTX_TIMESTAMP(base), 0);
	/* PDP values well be assigned later if needed */
	CTX_REG(regs, CTX_PDP3_UDW, GEN8_RING_PDP_UDW(engine, 3), 0);
	CTX_REG(regs, CTX_PDP3_LDW, GEN8_RING_PDP_LDW(engine, 3), 0);
	CTX_REG(regs, CTX_PDP2_UDW, GEN8_RING_PDP_UDW(engine, 2), 0);
	CTX_REG(regs, CTX_PDP2_LDW, GEN8_RING_PDP_LDW(engine, 2), 0);
	CTX_REG(regs, CTX_PDP1_UDW, GEN8_RING_PDP_UDW(engine, 1), 0);
	CTX_REG(regs, CTX_PDP1_LDW, GEN8_RING_PDP_LDW(engine, 1), 0);
	CTX_REG(regs, CTX_PDP0_UDW, GEN8_RING_PDP_UDW(engine, 0), 0);
	CTX_REG(regs, CTX_PDP0_LDW, GEN8_RING_PDP_LDW(engine, 0), 0);

	if (ppgtt && i915_vm_is_48bit(&ppgtt->vm)) {
		/* 64b PPGTT (48bit canonical)
		 * PDP0_DESCRIPTOR contains the base address to PML4 and
		 * other PDP Descriptors are ignored.
		 */
		ASSIGN_CTX_PML4(ppgtt, regs);
	}

	if (rcs) {
		regs[CTX_LRI_HEADER_2] = MI_LOAD_REGISTER_IMM(1);
		CTX_REG(regs, CTX_R_PWR_CLK_STATE, GEN8_R_PWR_CLK_STATE,
			make_rpcs(dev_priv));

		i915_oa_init_reg_state(engine, ctx, regs);
	}
}