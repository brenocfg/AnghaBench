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
struct TYPE_4__ {int /*<<< orphan*/  load_luts; void* load_csc_matrix; } ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ degamma_lut_size; scalar_t__ gamma_lut_size; } ;
struct TYPE_6__ {TYPE_2__ color; } ;

/* Variables and functions */
 TYPE_3__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  broadwell_load_luts ; 
 void* cherryview_load_csc_matrix ; 
 int /*<<< orphan*/  cherryview_load_luts ; 
 int /*<<< orphan*/  drm_crtc_enable_color_mgmt (struct drm_crtc*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  glk_load_luts ; 
 int /*<<< orphan*/  haswell_load_luts ; 
 int /*<<< orphan*/  i9xx_load_luts ; 
 void* ilk_load_csc_matrix ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_color_init(struct drm_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->dev);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	if (IS_CHERRYVIEW(dev_priv)) {
		dev_priv->display.load_csc_matrix = cherryview_load_csc_matrix;
		dev_priv->display.load_luts = cherryview_load_luts;
	} else if (IS_HASWELL(dev_priv)) {
		dev_priv->display.load_csc_matrix = ilk_load_csc_matrix;
		dev_priv->display.load_luts = haswell_load_luts;
	} else if (IS_BROADWELL(dev_priv) || IS_GEN9_BC(dev_priv) ||
		   IS_BROXTON(dev_priv)) {
		dev_priv->display.load_csc_matrix = ilk_load_csc_matrix;
		dev_priv->display.load_luts = broadwell_load_luts;
	} else if (IS_GEMINILAKE(dev_priv) || IS_CANNONLAKE(dev_priv)) {
		dev_priv->display.load_csc_matrix = ilk_load_csc_matrix;
		dev_priv->display.load_luts = glk_load_luts;
	} else {
		dev_priv->display.load_luts = i9xx_load_luts;
	}

	/* Enable color management support when we have degamma & gamma LUTs. */
	if (INTEL_INFO(dev_priv)->color.degamma_lut_size != 0 &&
	    INTEL_INFO(dev_priv)->color.gamma_lut_size != 0)
		drm_crtc_enable_color_mgmt(crtc,
					   INTEL_INFO(dev_priv)->color.degamma_lut_size,
					   true,
					   INTEL_INFO(dev_priv)->color.gamma_lut_size);
}