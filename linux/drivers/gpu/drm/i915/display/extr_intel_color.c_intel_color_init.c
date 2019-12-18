#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_3__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  load_luts; void* color_commit; void* color_check; } ;
struct drm_i915_private {TYPE_1__ display; } ;
struct TYPE_7__ {scalar_t__ degamma_lut_size; int /*<<< orphan*/  gamma_lut_size; } ;
struct TYPE_9__ {TYPE_2__ color; } ;

/* Variables and functions */
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_5__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bdw_load_luts ; 
 void* chv_color_check ; 
 int /*<<< orphan*/  chv_load_luts ; 
 int /*<<< orphan*/  drm_crtc_enable_color_mgmt (TYPE_3__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (TYPE_3__*,int) ; 
 void* glk_color_check ; 
 int /*<<< orphan*/  glk_load_luts ; 
 void* hsw_color_commit ; 
 int /*<<< orphan*/  i965_load_luts ; 
 void* i9xx_color_check ; 
 void* i9xx_color_commit ; 
 int /*<<< orphan*/  i9xx_load_luts ; 
 void* icl_color_check ; 
 int /*<<< orphan*/  icl_load_luts ; 
 void* ilk_color_check ; 
 void* ilk_color_commit ; 
 int /*<<< orphan*/  ilk_load_luts ; 
 void* ivb_color_check ; 
 int /*<<< orphan*/  ivb_load_luts ; 
 void* skl_color_commit ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_color_init(struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	bool has_ctm = INTEL_INFO(dev_priv)->color.degamma_lut_size != 0;

	drm_mode_crtc_set_gamma_size(&crtc->base, 256);

	if (HAS_GMCH(dev_priv)) {
		if (IS_CHERRYVIEW(dev_priv)) {
			dev_priv->display.color_check = chv_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = chv_load_luts;
		} else if (INTEL_GEN(dev_priv) >= 4) {
			dev_priv->display.color_check = i9xx_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = i965_load_luts;
		} else {
			dev_priv->display.color_check = i9xx_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = i9xx_load_luts;
		}
	} else {
		if (INTEL_GEN(dev_priv) >= 11)
			dev_priv->display.color_check = icl_color_check;
		else if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
			dev_priv->display.color_check = glk_color_check;
		else if (INTEL_GEN(dev_priv) >= 7)
			dev_priv->display.color_check = ivb_color_check;
		else
			dev_priv->display.color_check = ilk_color_check;

		if (INTEL_GEN(dev_priv) >= 9)
			dev_priv->display.color_commit = skl_color_commit;
		else if (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
			dev_priv->display.color_commit = hsw_color_commit;
		else
			dev_priv->display.color_commit = ilk_color_commit;

		if (INTEL_GEN(dev_priv) >= 11)
			dev_priv->display.load_luts = icl_load_luts;
		else if (IS_CANNONLAKE(dev_priv) || IS_GEMINILAKE(dev_priv))
			dev_priv->display.load_luts = glk_load_luts;
		else if (INTEL_GEN(dev_priv) >= 8)
			dev_priv->display.load_luts = bdw_load_luts;
		else if (INTEL_GEN(dev_priv) >= 7)
			dev_priv->display.load_luts = ivb_load_luts;
		else
			dev_priv->display.load_luts = ilk_load_luts;
	}

	drm_crtc_enable_color_mgmt(&crtc->base,
				   INTEL_INFO(dev_priv)->color.degamma_lut_size,
				   has_ctm,
				   INTEL_INFO(dev_priv)->color.gamma_lut_size);
}