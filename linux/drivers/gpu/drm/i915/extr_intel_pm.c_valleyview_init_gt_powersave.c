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
struct intel_rps {int /*<<< orphan*/  min_freq; int /*<<< orphan*/  rp1_freq; int /*<<< orphan*/  efficient_freq; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  rp0_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int mem_freq; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,...) ; 
 int /*<<< orphan*/  PUNIT_REG_GPU_FREQ_STS ; 
 int /*<<< orphan*/  VLV_IOSF_SB_CCK ; 
 int /*<<< orphan*/  VLV_IOSF_SB_NC ; 
 int /*<<< orphan*/  VLV_IOSF_SB_PUNIT ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valleyview_rps_guar_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_rps_max_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_rps_min_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_rps_rpe_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_setup_pctx (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_init_gpll_ref_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_iosf_sb_get (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int) ; 
 int vlv_punit_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void valleyview_init_gt_powersave(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 val;

	valleyview_setup_pctx(dev_priv);

	vlv_iosf_sb_get(dev_priv,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	vlv_init_gpll_ref_freq(dev_priv);

	val = vlv_punit_read(dev_priv, PUNIT_REG_GPU_FREQ_STS);
	switch ((val >> 6) & 3) {
	case 0:
	case 1:
		dev_priv->mem_freq = 800;
		break;
	case 2:
		dev_priv->mem_freq = 1066;
		break;
	case 3:
		dev_priv->mem_freq = 1333;
		break;
	}
	DRM_DEBUG_DRIVER("DDR speed: %d MHz\n", dev_priv->mem_freq);

	rps->max_freq = valleyview_rps_max_freq(dev_priv);
	rps->rp0_freq = rps->max_freq;
	DRM_DEBUG_DRIVER("max GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->max_freq),
			 rps->max_freq);

	rps->efficient_freq = valleyview_rps_rpe_freq(dev_priv);
	DRM_DEBUG_DRIVER("RPe GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->efficient_freq),
			 rps->efficient_freq);

	rps->rp1_freq = valleyview_rps_guar_freq(dev_priv);
	DRM_DEBUG_DRIVER("RP1(Guar Freq) GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->rp1_freq),
			 rps->rp1_freq);

	rps->min_freq = valleyview_rps_min_freq(dev_priv);
	DRM_DEBUG_DRIVER("min GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->min_freq),
			 rps->min_freq);

	vlv_iosf_sb_put(dev_priv,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));
}