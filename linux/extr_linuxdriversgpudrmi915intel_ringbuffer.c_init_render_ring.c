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
struct intel_engine_cs {int /*<<< orphan*/  irq_keep_mask; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_FLIP_PERF_DISABLE ; 
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  CM0_STC_EVICT_DISABLE_LRA_SNB ; 
 int /*<<< orphan*/  GFX_MODE ; 
 int /*<<< orphan*/  GFX_MODE_GEN7 ; 
 int /*<<< orphan*/  GFX_REPLAY_MODE ; 
 int /*<<< orphan*/  GFX_TLB_INVALIDATE_EXPLICIT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_IMR (struct intel_engine_cs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTPM ; 
 int /*<<< orphan*/  INSTPM_FORCE_ORDERING ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int,int) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MI_MODE ; 
 int /*<<< orphan*/  VS_TIMER_DISPATCH ; 
 int _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int init_ring_common (struct intel_engine_cs*) ; 
 int /*<<< orphan*/  intel_whitelist_workarounds_apply (struct intel_engine_cs*) ; 

__attribute__((used)) static int init_render_ring(struct intel_engine_cs *engine)
{
	struct drm_i915_private *dev_priv = engine->i915;
	int ret = init_ring_common(engine);
	if (ret)
		return ret;

	intel_whitelist_workarounds_apply(engine);

	/* WaTimedSingleVertexDispatch:cl,bw,ctg,elk,ilk,snb */
	if (IS_GEN(dev_priv, 4, 6))
		I915_WRITE(MI_MODE, _MASKED_BIT_ENABLE(VS_TIMER_DISPATCH));

	/* We need to disable the AsyncFlip performance optimisations in order
	 * to use MI_WAIT_FOR_EVENT within the CS. It should already be
	 * programmed to '1' on all products.
	 *
	 * WaDisableAsyncFlipPerfMode:snb,ivb,hsw,vlv
	 */
	if (IS_GEN(dev_priv, 6, 7))
		I915_WRITE(MI_MODE, _MASKED_BIT_ENABLE(ASYNC_FLIP_PERF_DISABLE));

	/* Required for the hardware to program scanline values for waiting */
	/* WaEnableFlushTlbInvalidationMode:snb */
	if (IS_GEN6(dev_priv))
		I915_WRITE(GFX_MODE,
			   _MASKED_BIT_ENABLE(GFX_TLB_INVALIDATE_EXPLICIT));

	/* WaBCSVCSTlbInvalidationMode:ivb,vlv,hsw */
	if (IS_GEN7(dev_priv))
		I915_WRITE(GFX_MODE_GEN7,
			   _MASKED_BIT_ENABLE(GFX_TLB_INVALIDATE_EXPLICIT) |
			   _MASKED_BIT_ENABLE(GFX_REPLAY_MODE));

	if (IS_GEN6(dev_priv)) {
		/* From the Sandybridge PRM, volume 1 part 3, page 24:
		 * "If this bit is set, STCunit will have LRA as replacement
		 *  policy. [...] This bit must be reset.  LRA replacement
		 *  policy is not supported."
		 */
		I915_WRITE(CACHE_MODE_0,
			   _MASKED_BIT_DISABLE(CM0_STC_EVICT_DISABLE_LRA_SNB));
	}

	if (IS_GEN(dev_priv, 6, 7))
		I915_WRITE(INSTPM, _MASKED_BIT_ENABLE(INSTPM_FORCE_ORDERING));

	if (INTEL_GEN(dev_priv) >= 6)
		I915_WRITE_IMR(engine, ~engine->irq_keep_mask);

	return 0;
}