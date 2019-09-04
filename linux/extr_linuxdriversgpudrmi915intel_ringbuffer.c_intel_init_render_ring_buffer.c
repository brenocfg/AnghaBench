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
struct intel_engine_cs {int /*<<< orphan*/  init_hw; int /*<<< orphan*/  emit_bb_start; int /*<<< orphan*/  irq_enable_mask; void* emit_flush; int /*<<< orphan*/  init_context; int /*<<< orphan*/  irq_keep_mask; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_RENDER_L3_PARITY_ERROR_INTERRUPT ; 
 int /*<<< orphan*/  GT_RENDER_USER_INTERRUPT ; 
 scalar_t__ HAS_L3_DPF (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_USER_INTERRUPT ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN5 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 void* gen2_render_ring_flush ; 
 void* gen4_render_ring_flush ; 
 void* gen6_render_ring_flush ; 
 void* gen7_render_ring_flush ; 
 int /*<<< orphan*/  hsw_emit_bb_start ; 
 int /*<<< orphan*/  init_render_ring ; 
 int intel_init_ring_buffer (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_rcs_ctx_init ; 
 int /*<<< orphan*/  intel_ring_default_vfuncs (struct drm_i915_private*,struct intel_engine_cs*) ; 

int intel_init_render_ring_buffer(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret;

	intel_ring_default_vfuncs(dev_priv, engine);

	if (HAS_L3_DPF(dev_priv))
		engine->irq_keep_mask = GT_RENDER_L3_PARITY_ERROR_INTERRUPT;

	engine->irq_enable_mask = GT_RENDER_USER_INTERRUPT;

	if (INTEL_GEN(dev_priv) >= 6) {
		engine->init_context = intel_rcs_ctx_init;
		engine->emit_flush = gen7_render_ring_flush;
		if (IS_GEN6(dev_priv))
			engine->emit_flush = gen6_render_ring_flush;
	} else if (IS_GEN5(dev_priv)) {
		engine->emit_flush = gen4_render_ring_flush;
	} else {
		if (INTEL_GEN(dev_priv) < 4)
			engine->emit_flush = gen2_render_ring_flush;
		else
			engine->emit_flush = gen4_render_ring_flush;
		engine->irq_enable_mask = I915_USER_INTERRUPT;
	}

	if (IS_HASWELL(dev_priv))
		engine->emit_bb_start = hsw_emit_bb_start;

	engine->init_hw = init_render_ring;

	ret = intel_init_ring_buffer(engine);
	if (ret)
		return ret;

	return 0;
}