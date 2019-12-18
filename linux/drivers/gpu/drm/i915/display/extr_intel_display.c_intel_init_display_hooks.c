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
struct TYPE_2__ {int /*<<< orphan*/  update_crtcs; int /*<<< orphan*/  fdi_link_train; void* crtc_disable; void* crtc_enable; void* crtc_compute_clock; void* get_initial_plane_config; void* get_pipe_config; } ;
struct drm_i915_private {TYPE_1__ display; } ;

/* Variables and functions */
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 void* chv_crtc_compute_clock ; 
 void* g4x_crtc_compute_clock ; 
 int /*<<< orphan*/  gen6_fdi_link_train ; 
 void* haswell_crtc_compute_clock ; 
 void* haswell_crtc_disable ; 
 void* haswell_crtc_enable ; 
 void* haswell_get_pipe_config ; 
 int /*<<< orphan*/  hsw_fdi_link_train ; 
 void* i8xx_crtc_compute_clock ; 
 void* i9xx_crtc_compute_clock ; 
 void* i9xx_crtc_disable ; 
 void* i9xx_crtc_enable ; 
 void* i9xx_get_initial_plane_config ; 
 void* i9xx_get_pipe_config ; 
 int /*<<< orphan*/  intel_init_cdclk_hooks (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_update_crtcs ; 
 void* ironlake_crtc_compute_clock ; 
 void* ironlake_crtc_disable ; 
 void* ironlake_crtc_enable ; 
 int /*<<< orphan*/  ironlake_fdi_link_train ; 
 void* ironlake_get_pipe_config ; 
 int /*<<< orphan*/  ivb_manual_fdi_link_train ; 
 void* pnv_crtc_compute_clock ; 
 int /*<<< orphan*/  skl_update_crtcs ; 
 void* skylake_get_initial_plane_config ; 
 void* valleyview_crtc_enable ; 
 void* vlv_crtc_compute_clock ; 

void intel_init_display_hooks(struct drm_i915_private *dev_priv)
{
	intel_init_cdclk_hooks(dev_priv);

	if (INTEL_GEN(dev_priv) >= 9) {
		dev_priv->display.get_pipe_config = haswell_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			skylake_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock =
			haswell_crtc_compute_clock;
		dev_priv->display.crtc_enable = haswell_crtc_enable;
		dev_priv->display.crtc_disable = haswell_crtc_disable;
	} else if (HAS_DDI(dev_priv)) {
		dev_priv->display.get_pipe_config = haswell_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock =
			haswell_crtc_compute_clock;
		dev_priv->display.crtc_enable = haswell_crtc_enable;
		dev_priv->display.crtc_disable = haswell_crtc_disable;
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		dev_priv->display.get_pipe_config = ironlake_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock =
			ironlake_crtc_compute_clock;
		dev_priv->display.crtc_enable = ironlake_crtc_enable;
		dev_priv->display.crtc_disable = ironlake_crtc_disable;
	} else if (IS_CHERRYVIEW(dev_priv)) {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = chv_crtc_compute_clock;
		dev_priv->display.crtc_enable = valleyview_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	} else if (IS_VALLEYVIEW(dev_priv)) {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = vlv_crtc_compute_clock;
		dev_priv->display.crtc_enable = valleyview_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	} else if (IS_G4X(dev_priv)) {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = g4x_crtc_compute_clock;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	} else if (IS_PINEVIEW(dev_priv)) {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = pnv_crtc_compute_clock;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	} else if (!IS_GEN(dev_priv, 2)) {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = i9xx_crtc_compute_clock;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	} else {
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.get_initial_plane_config =
			i9xx_get_initial_plane_config;
		dev_priv->display.crtc_compute_clock = i8xx_crtc_compute_clock;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	}

	if (IS_GEN(dev_priv, 5)) {
		dev_priv->display.fdi_link_train = ironlake_fdi_link_train;
	} else if (IS_GEN(dev_priv, 6)) {
		dev_priv->display.fdi_link_train = gen6_fdi_link_train;
	} else if (IS_IVYBRIDGE(dev_priv)) {
		/* FIXME: detect B0+ stepping and use auto training */
		dev_priv->display.fdi_link_train = ivb_manual_fdi_link_train;
	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		dev_priv->display.fdi_link_train = hsw_fdi_link_train;
	}

	if (INTEL_GEN(dev_priv) >= 9)
		dev_priv->display.update_crtcs = skl_update_crtcs;
	else
		dev_priv->display.update_crtcs = intel_update_crtcs;
}