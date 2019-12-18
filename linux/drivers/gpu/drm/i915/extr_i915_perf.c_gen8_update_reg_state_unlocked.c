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
typedef  scalar_t__ u32 ;
struct intel_context {int /*<<< orphan*/  sseu; TYPE_1__* engine; } ;
struct i915_perf_stream {int period_exponent; scalar_t__ periodic; } ;
struct i915_oa_config {int dummy; } ;
struct TYPE_4__ {scalar_t__ ctx_flexeu0_offset; scalar_t__ ctx_oactxctrl_offset; } ;
struct drm_i915_private {TYPE_2__ perf; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_3__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CTX_REG (scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CTX_R_PWR_CLK_STATE ; 
 int /*<<< orphan*/  EU_PERF_CNTL0 ; 
 int /*<<< orphan*/  EU_PERF_CNTL1 ; 
 int /*<<< orphan*/  EU_PERF_CNTL2 ; 
 int /*<<< orphan*/  EU_PERF_CNTL3 ; 
 int /*<<< orphan*/  EU_PERF_CNTL4 ; 
 int /*<<< orphan*/  EU_PERF_CNTL5 ; 
 int /*<<< orphan*/  EU_PERF_CNTL6 ; 
 int /*<<< orphan*/  GEN8_OACTXCONTROL ; 
 int GEN8_OA_COUNTER_RESUME ; 
 int GEN8_OA_TIMER_ENABLE ; 
 int GEN8_OA_TIMER_PERIOD_SHIFT ; 
 int /*<<< orphan*/  GEN8_R_PWR_CLK_STATE ; 
 int intel_sseu_make_rpcs (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int oa_config_flex_reg (struct i915_oa_config const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen8_update_reg_state_unlocked(struct i915_perf_stream *stream,
			       struct intel_context *ce,
			       u32 *reg_state,
			       const struct i915_oa_config *oa_config)
{
	struct drm_i915_private *i915 = ce->engine->i915;
	u32 ctx_oactxctrl = i915->perf.ctx_oactxctrl_offset;
	u32 ctx_flexeu0 = i915->perf.ctx_flexeu0_offset;
	/* The MMIO offsets for Flex EU registers aren't contiguous */
	i915_reg_t flex_regs[] = {
		EU_PERF_CNTL0,
		EU_PERF_CNTL1,
		EU_PERF_CNTL2,
		EU_PERF_CNTL3,
		EU_PERF_CNTL4,
		EU_PERF_CNTL5,
		EU_PERF_CNTL6,
	};
	int i;

	CTX_REG(reg_state, ctx_oactxctrl, GEN8_OACTXCONTROL,
		(stream->period_exponent << GEN8_OA_TIMER_PERIOD_SHIFT) |
		(stream->periodic ? GEN8_OA_TIMER_ENABLE : 0) |
		GEN8_OA_COUNTER_RESUME);

	for (i = 0; i < ARRAY_SIZE(flex_regs); i++) {
		CTX_REG(reg_state, ctx_flexeu0 + i * 2, flex_regs[i],
			oa_config_flex_reg(oa_config, flex_regs[i]));
	}

	CTX_REG(reg_state,
		CTX_R_PWR_CLK_STATE, GEN8_R_PWR_CLK_STATE,
		intel_sseu_make_rpcs(i915, &ce->sseu));
}