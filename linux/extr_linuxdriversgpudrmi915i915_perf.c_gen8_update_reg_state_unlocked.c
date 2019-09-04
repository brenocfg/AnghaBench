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
typedef  size_t u32 ;
struct i915_oa_config {size_t flex_regs_len; TYPE_3__* flex_regs; } ;
struct i915_gem_context {struct drm_i915_private* i915; } ;
struct TYPE_4__ {size_t ctx_oactxctrl_offset; size_t ctx_flexeu0_offset; size_t period_exponent; scalar_t__ periodic; } ;
struct TYPE_5__ {TYPE_1__ oa; } ;
struct drm_i915_private {TYPE_2__ perf; } ;
struct TYPE_6__ {size_t value; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 int /*<<< orphan*/  EU_PERF_CNTL0 ; 
 int /*<<< orphan*/  EU_PERF_CNTL1 ; 
 int /*<<< orphan*/  EU_PERF_CNTL2 ; 
 int /*<<< orphan*/  EU_PERF_CNTL3 ; 
 int /*<<< orphan*/  EU_PERF_CNTL4 ; 
 int /*<<< orphan*/  EU_PERF_CNTL5 ; 
 int /*<<< orphan*/  EU_PERF_CNTL6 ; 
 int /*<<< orphan*/  GEN8_OACTXCONTROL ; 
 size_t GEN8_OA_COUNTER_RESUME ; 
 size_t GEN8_OA_TIMER_ENABLE ; 
 size_t GEN8_OA_TIMER_PERIOD_SHIFT ; 
 size_t i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_update_reg_state_unlocked(struct i915_gem_context *ctx,
					   u32 *reg_state,
					   const struct i915_oa_config *oa_config)
{
	struct drm_i915_private *dev_priv = ctx->i915;
	u32 ctx_oactxctrl = dev_priv->perf.oa.ctx_oactxctrl_offset;
	u32 ctx_flexeu0 = dev_priv->perf.oa.ctx_flexeu0_offset;
	/* The MMIO offsets for Flex EU registers aren't contiguous */
	u32 flex_mmio[] = {
		i915_mmio_reg_offset(EU_PERF_CNTL0),
		i915_mmio_reg_offset(EU_PERF_CNTL1),
		i915_mmio_reg_offset(EU_PERF_CNTL2),
		i915_mmio_reg_offset(EU_PERF_CNTL3),
		i915_mmio_reg_offset(EU_PERF_CNTL4),
		i915_mmio_reg_offset(EU_PERF_CNTL5),
		i915_mmio_reg_offset(EU_PERF_CNTL6),
	};
	int i;

	reg_state[ctx_oactxctrl] = i915_mmio_reg_offset(GEN8_OACTXCONTROL);
	reg_state[ctx_oactxctrl+1] = (dev_priv->perf.oa.period_exponent <<
				      GEN8_OA_TIMER_PERIOD_SHIFT) |
				     (dev_priv->perf.oa.periodic ?
				      GEN8_OA_TIMER_ENABLE : 0) |
				     GEN8_OA_COUNTER_RESUME;

	for (i = 0; i < ARRAY_SIZE(flex_mmio); i++) {
		u32 state_offset = ctx_flexeu0 + i * 2;
		u32 mmio = flex_mmio[i];

		/*
		 * This arbitrary default will select the 'EU FPU0 Pipeline
		 * Active' event. In the future it's anticipated that there
		 * will be an explicit 'No Event' we can select, but not yet...
		 */
		u32 value = 0;

		if (oa_config) {
			u32 j;

			for (j = 0; j < oa_config->flex_regs_len; j++) {
				if (i915_mmio_reg_offset(oa_config->flex_regs[j].addr) == mmio) {
					value = oa_config->flex_regs[j].value;
					break;
				}
			}
		}

		reg_state[state_offset] = mmio;
		reg_state[state_offset+1] = value;
	}
}