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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  last_init_time; } ;
struct drm_i915_private {int /*<<< orphan*/  wopcm; int /*<<< orphan*/  gpu_error; int /*<<< orphan*/  kernel_context; TYPE_1__ gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EIO ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN7_MSG_CTL ; 
 scalar_t__ HAS_EDRAM (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_NOP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_IDICR ; 
 int /*<<< orphan*/  HSW_NDE_RSTWRN_OPT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int IDIHASHMSK (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HSW_GT3 (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int LOWER_SLICE_DISABLED ; 
 int LOWER_SLICE_ENABLED ; 
 int /*<<< orphan*/  MI_PREDICATE_RESULT_2 ; 
 int RESET_PCH_HANDSHAKE_ENABLE ; 
 int WAIT_FOR_PCH_FLR_ACK ; 
 int WAIT_FOR_PCH_RESET_ACK ; 
 int __i915_gem_restart_engines (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_init_swizzling (struct drm_i915_private*) ; 
 int i915_ppgtt_init_hw (struct drm_i915_private*) ; 
 scalar_t__ i915_terminally_wedged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_unused_rings (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_mocs_init_l3cc_table (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_fini_hw (struct drm_i915_private*) ; 
 int intel_uc_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_wopcm_init_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 

int i915_gem_init_hw(struct drm_i915_private *dev_priv)
{
	int ret;

	dev_priv->gt.last_init_time = ktime_get();

	/* Double layer security blanket, see i915_gem_init() */
	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);

	if (HAS_EDRAM(dev_priv) && INTEL_GEN(dev_priv) < 9)
		I915_WRITE(HSW_IDICR, I915_READ(HSW_IDICR) | IDIHASHMSK(0xf));

	if (IS_HASWELL(dev_priv))
		I915_WRITE(MI_PREDICATE_RESULT_2, IS_HSW_GT3(dev_priv) ?
			   LOWER_SLICE_ENABLED : LOWER_SLICE_DISABLED);

	if (HAS_PCH_NOP(dev_priv)) {
		if (IS_IVYBRIDGE(dev_priv)) {
			u32 temp = I915_READ(GEN7_MSG_CTL);
			temp &= ~(WAIT_FOR_PCH_FLR_ACK | WAIT_FOR_PCH_RESET_ACK);
			I915_WRITE(GEN7_MSG_CTL, temp);
		} else if (INTEL_GEN(dev_priv) >= 7) {
			u32 temp = I915_READ(HSW_NDE_RSTWRN_OPT);
			temp &= ~RESET_PCH_HANDSHAKE_ENABLE;
			I915_WRITE(HSW_NDE_RSTWRN_OPT, temp);
		}
	}

	intel_gt_workarounds_apply(dev_priv);

	i915_gem_init_swizzling(dev_priv);

	/*
	 * At least 830 can leave some of the unused rings
	 * "active" (ie. head != tail) after resume which
	 * will prevent c3 entry. Makes sure all unused rings
	 * are totally idle.
	 */
	init_unused_rings(dev_priv);

	BUG_ON(!dev_priv->kernel_context);
	if (i915_terminally_wedged(&dev_priv->gpu_error)) {
		ret = -EIO;
		goto out;
	}

	ret = i915_ppgtt_init_hw(dev_priv);
	if (ret) {
		DRM_ERROR("Enabling PPGTT failed (%d)\n", ret);
		goto out;
	}

	ret = intel_wopcm_init_hw(&dev_priv->wopcm);
	if (ret) {
		DRM_ERROR("Enabling WOPCM failed (%d)\n", ret);
		goto out;
	}

	/* We can't enable contexts until all firmware is loaded */
	ret = intel_uc_init_hw(dev_priv);
	if (ret) {
		DRM_ERROR("Enabling uc failed (%d)\n", ret);
		goto out;
	}

	intel_mocs_init_l3cc_table(dev_priv);

	/* Only when the HW is re-initialised, can we replay the requests */
	ret = __i915_gem_restart_engines(dev_priv);
	if (ret)
		goto cleanup_uc;

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);

	return 0;

cleanup_uc:
	intel_uc_fini_hw(dev_priv);
out:
	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);

	return ret;
}