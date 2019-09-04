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
struct i915_request {struct drm_i915_private* i915; } ;
struct i915_oa_config {size_t flex_regs_len; TYPE_3__* flex_regs; } ;
struct TYPE_4__ {int period_exponent; scalar_t__ periodic; } ;
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
 int GEN8_OA_COUNTER_RESUME ; 
 int GEN8_OA_TIMER_ENABLE ; 
 int GEN8_OA_TIMER_PERIOD_SHIFT ; 
 scalar_t__ IS_ERR (size_t*) ; 
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  MI_NOOP ; 
 int PTR_ERR (size_t*) ; 
 size_t i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ring_advance (struct i915_request*,size_t*) ; 
 size_t* intel_ring_begin (struct i915_request*,int) ; 

__attribute__((used)) static int gen8_emit_oa_config(struct i915_request *rq,
			       const struct i915_oa_config *oa_config)
{
	struct drm_i915_private *dev_priv = rq->i915;
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
	u32 *cs;
	int i;

	cs = intel_ring_begin(rq, ARRAY_SIZE(flex_mmio) * 2 + 4);
	if (IS_ERR(cs))
		return PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(ARRAY_SIZE(flex_mmio) + 1);

	*cs++ = i915_mmio_reg_offset(GEN8_OACTXCONTROL);
	*cs++ = (dev_priv->perf.oa.period_exponent << GEN8_OA_TIMER_PERIOD_SHIFT) |
		(dev_priv->perf.oa.periodic ? GEN8_OA_TIMER_ENABLE : 0) |
		GEN8_OA_COUNTER_RESUME;

	for (i = 0; i < ARRAY_SIZE(flex_mmio); i++) {
		u32 mmio = flex_mmio[i];

		/*
		 * This arbitrary default will select the 'EU FPU0 Pipeline
		 * Active' event. In the future it's anticipated that there
		 * will be an explicit 'No Event' we can select, but not
		 * yet...
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

		*cs++ = mmio;
		*cs++ = value;
	}

	*cs++ = MI_NOOP;
	intel_ring_advance(rq, cs);

	return 0;
}