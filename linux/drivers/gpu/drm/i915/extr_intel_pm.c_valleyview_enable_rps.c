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
typedef  int u32 ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN6_RP_CONTROL ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_EI ; 
 int GEN6_RP_DOWN_IDLE_CONT ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_TIMEOUT ; 
 int GEN6_RP_ENABLE ; 
 int /*<<< orphan*/  GEN6_RP_IDLE_HYSTERSIS ; 
 int GEN6_RP_MEDIA_HW_NORMAL_MODE ; 
 int GEN6_RP_MEDIA_IS_GFX ; 
 int GEN6_RP_MEDIA_TURBO ; 
 int GEN6_RP_UP_BUSY_AVG ; 
 int /*<<< orphan*/  GEN6_RP_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_UP_THRESHOLD ; 
 int GPLLENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PUNIT_REG_GPU_FREQ_STS ; 
 int VLV_BIAS_CPU_125_SOC_875 ; 
 int VLV_OVERRIDE_EN ; 
 int VLV_SOC_TDP_EN ; 
 int /*<<< orphan*/  VLV_TURBO_SOC_OVERRIDE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_rps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valleyview_set_rps ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int yesno (int) ; 

__attribute__((used)) static void valleyview_enable_rps(struct drm_i915_private *dev_priv)
{
	u32 val;

	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	I915_WRITE(GEN6_RP_DOWN_TIMEOUT, 1000000);
	I915_WRITE(GEN6_RP_UP_THRESHOLD, 59400);
	I915_WRITE(GEN6_RP_DOWN_THRESHOLD, 245000);
	I915_WRITE(GEN6_RP_UP_EI, 66000);
	I915_WRITE(GEN6_RP_DOWN_EI, 350000);

	I915_WRITE(GEN6_RP_IDLE_HYSTERSIS, 10);

	I915_WRITE(GEN6_RP_CONTROL,
		   GEN6_RP_MEDIA_TURBO |
		   GEN6_RP_MEDIA_HW_NORMAL_MODE |
		   GEN6_RP_MEDIA_IS_GFX |
		   GEN6_RP_ENABLE |
		   GEN6_RP_UP_BUSY_AVG |
		   GEN6_RP_DOWN_IDLE_CONT);

	vlv_punit_get(dev_priv);

	/* Setting Fixed Bias */
	val = VLV_OVERRIDE_EN | VLV_SOC_TDP_EN | VLV_BIAS_CPU_125_SOC_875;
	vlv_punit_write(dev_priv, VLV_TURBO_SOC_OVERRIDE, val);

	val = vlv_punit_read(dev_priv, PUNIT_REG_GPU_FREQ_STS);

	vlv_punit_put(dev_priv);

	/* RPS code assumes GPLL is used */
	WARN_ONCE((val & GPLLENABLE) == 0, "GPLL not enabled\n");

	DRM_DEBUG_DRIVER("GPLL enabled? %s\n", yesno(val & GPLLENABLE));
	DRM_DEBUG_DRIVER("GPU status: 0x%08x\n", val);

	reset_rps(dev_priv, valleyview_set_rps);

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
}