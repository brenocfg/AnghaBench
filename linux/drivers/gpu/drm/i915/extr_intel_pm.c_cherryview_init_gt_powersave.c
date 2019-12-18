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
struct intel_rps {int max_freq; int rp0_freq; int efficient_freq; int rp1_freq; int min_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int mem_freq; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCK_FUSE_REG ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,...) ; 
 int /*<<< orphan*/  VLV_IOSF_SB_CCK ; 
 int /*<<< orphan*/  VLV_IOSF_SB_NC ; 
 int /*<<< orphan*/  VLV_IOSF_SB_PUNIT ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int cherryview_rps_guar_freq (struct drm_i915_private*) ; 
 int cherryview_rps_max_freq (struct drm_i915_private*) ; 
 int cherryview_rps_min_freq (struct drm_i915_private*) ; 
 int cherryview_rps_rpe_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cherryview_setup_pctx (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int) ; 
 int vlv_cck_read (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_init_gpll_ref_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_iosf_sb_get (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_iosf_sb_put (struct drm_i915_private*,int) ; 

__attribute__((used)) static void cherryview_init_gt_powersave(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 val;

	cherryview_setup_pctx(dev_priv);

	vlv_iosf_sb_get(dev_priv,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	vlv_init_gpll_ref_freq(dev_priv);

	val = vlv_cck_read(dev_priv, CCK_FUSE_REG);

	switch ((val >> 2) & 0x7) {
	case 3:
		dev_priv->mem_freq = 2000;
		break;
	default:
		dev_priv->mem_freq = 1600;
		break;
	}
	DRM_DEBUG_DRIVER("DDR speed: %d MHz\n", dev_priv->mem_freq);

	rps->max_freq = cherryview_rps_max_freq(dev_priv);
	rps->rp0_freq = rps->max_freq;
	DRM_DEBUG_DRIVER("max GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->max_freq),
			 rps->max_freq);

	rps->efficient_freq = cherryview_rps_rpe_freq(dev_priv);
	DRM_DEBUG_DRIVER("RPe GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->efficient_freq),
			 rps->efficient_freq);

	rps->rp1_freq = cherryview_rps_guar_freq(dev_priv);
	DRM_DEBUG_DRIVER("RP1(Guar) GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->rp1_freq),
			 rps->rp1_freq);

	rps->min_freq = cherryview_rps_min_freq(dev_priv);
	DRM_DEBUG_DRIVER("min GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, rps->min_freq),
			 rps->min_freq);

	vlv_iosf_sb_put(dev_priv,
			BIT(VLV_IOSF_SB_PUNIT) |
			BIT(VLV_IOSF_SB_NC) |
			BIT(VLV_IOSF_SB_CCK));

	WARN_ONCE((rps->max_freq | rps->efficient_freq | rps->rp1_freq |
		   rps->min_freq) & 1,
		  "Odd GPU freq values\n");
}