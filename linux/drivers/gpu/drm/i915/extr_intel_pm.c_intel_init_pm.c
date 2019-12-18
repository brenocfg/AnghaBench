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
struct TYPE_5__ {int /*<<< orphan*/  get_fifo_size; int /*<<< orphan*/ * update_wm; int /*<<< orphan*/  optimize_watermarks; int /*<<< orphan*/  initial_watermarks; int /*<<< orphan*/  compute_intermediate_wm; int /*<<< orphan*/  compute_pipe_wm; int /*<<< orphan*/  atomic_update_watermarks; int /*<<< orphan*/  compute_global_watermarks; } ;
struct TYPE_4__ {scalar_t__* cur_latency; scalar_t__* spr_latency; scalar_t__* pri_latency; } ;
struct drm_i915_private {int is_ddr3; TYPE_2__ display; int /*<<< orphan*/  mem_freq; int /*<<< orphan*/  fsb_freq; TYPE_1__ wm; } ;
struct TYPE_6__ {int num_pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 TYPE_3__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  IS_MOBILE (struct drm_i915_private*) ; 
 scalar_t__ IS_PINEVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  g4x_compute_intermediate_wm ; 
 int /*<<< orphan*/  g4x_compute_pipe_wm ; 
 int /*<<< orphan*/  g4x_initial_watermarks ; 
 int /*<<< orphan*/  g4x_optimize_watermarks ; 
 int /*<<< orphan*/  g4x_setup_wm_latency (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i830_get_fifo_size ; 
 int /*<<< orphan*/  i845_get_fifo_size ; 
 int /*<<< orphan*/ * i845_update_wm ; 
 int /*<<< orphan*/  i915_ironlake_get_mem_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_pineview_get_mem_freq (struct drm_i915_private*) ; 
 int /*<<< orphan*/ * i965_update_wm ; 
 int /*<<< orphan*/  i9xx_get_fifo_size ; 
 void* i9xx_update_wm ; 
 int /*<<< orphan*/  ilk_compute_intermediate_wm ; 
 int /*<<< orphan*/  ilk_compute_pipe_wm ; 
 int /*<<< orphan*/  ilk_initial_watermarks ; 
 int /*<<< orphan*/  ilk_optimize_watermarks ; 
 int /*<<< orphan*/  ilk_setup_wm_latency (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_get_cxsr_latency (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/ * pineview_update_wm ; 
 int /*<<< orphan*/  skl_atomic_update_crtc_wm ; 
 int /*<<< orphan*/  skl_compute_wm ; 
 int /*<<< orphan*/  skl_initial_wm ; 
 int /*<<< orphan*/  skl_setup_wm_latency (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_atomic_update_fifo ; 
 int /*<<< orphan*/  vlv_compute_intermediate_wm ; 
 int /*<<< orphan*/  vlv_compute_pipe_wm ; 
 int /*<<< orphan*/  vlv_initial_watermarks ; 
 int /*<<< orphan*/  vlv_optimize_watermarks ; 
 int /*<<< orphan*/  vlv_setup_wm_latency (struct drm_i915_private*) ; 

void intel_init_pm(struct drm_i915_private *dev_priv)
{
	/* For cxsr */
	if (IS_PINEVIEW(dev_priv))
		i915_pineview_get_mem_freq(dev_priv);
	else if (IS_GEN(dev_priv, 5))
		i915_ironlake_get_mem_freq(dev_priv);

	/* For FIFO watermark updates */
	if (INTEL_GEN(dev_priv) >= 9) {
		skl_setup_wm_latency(dev_priv);
		dev_priv->display.initial_watermarks = skl_initial_wm;
		dev_priv->display.atomic_update_watermarks = skl_atomic_update_crtc_wm;
		dev_priv->display.compute_global_watermarks = skl_compute_wm;
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		ilk_setup_wm_latency(dev_priv);

		if ((IS_GEN(dev_priv, 5) && dev_priv->wm.pri_latency[1] &&
		     dev_priv->wm.spr_latency[1] && dev_priv->wm.cur_latency[1]) ||
		    (!IS_GEN(dev_priv, 5) && dev_priv->wm.pri_latency[0] &&
		     dev_priv->wm.spr_latency[0] && dev_priv->wm.cur_latency[0])) {
			dev_priv->display.compute_pipe_wm = ilk_compute_pipe_wm;
			dev_priv->display.compute_intermediate_wm =
				ilk_compute_intermediate_wm;
			dev_priv->display.initial_watermarks =
				ilk_initial_watermarks;
			dev_priv->display.optimize_watermarks =
				ilk_optimize_watermarks;
		} else {
			DRM_DEBUG_KMS("Failed to read display plane latency. "
				      "Disable CxSR\n");
		}
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		vlv_setup_wm_latency(dev_priv);
		dev_priv->display.compute_pipe_wm = vlv_compute_pipe_wm;
		dev_priv->display.compute_intermediate_wm = vlv_compute_intermediate_wm;
		dev_priv->display.initial_watermarks = vlv_initial_watermarks;
		dev_priv->display.optimize_watermarks = vlv_optimize_watermarks;
		dev_priv->display.atomic_update_watermarks = vlv_atomic_update_fifo;
	} else if (IS_G4X(dev_priv)) {
		g4x_setup_wm_latency(dev_priv);
		dev_priv->display.compute_pipe_wm = g4x_compute_pipe_wm;
		dev_priv->display.compute_intermediate_wm = g4x_compute_intermediate_wm;
		dev_priv->display.initial_watermarks = g4x_initial_watermarks;
		dev_priv->display.optimize_watermarks = g4x_optimize_watermarks;
	} else if (IS_PINEVIEW(dev_priv)) {
		if (!intel_get_cxsr_latency(!IS_MOBILE(dev_priv),
					    dev_priv->is_ddr3,
					    dev_priv->fsb_freq,
					    dev_priv->mem_freq)) {
			DRM_INFO("failed to find known CxSR latency "
				 "(found ddr%s fsb freq %d, mem freq %d), "
				 "disabling CxSR\n",
				 (dev_priv->is_ddr3 == 1) ? "3" : "2",
				 dev_priv->fsb_freq, dev_priv->mem_freq);
			/* Disable CxSR and never update its watermark again */
			intel_set_memory_cxsr(dev_priv, false);
			dev_priv->display.update_wm = NULL;
		} else
			dev_priv->display.update_wm = pineview_update_wm;
	} else if (IS_GEN(dev_priv, 4)) {
		dev_priv->display.update_wm = i965_update_wm;
	} else if (IS_GEN(dev_priv, 3)) {
		dev_priv->display.update_wm = i9xx_update_wm;
		dev_priv->display.get_fifo_size = i9xx_get_fifo_size;
	} else if (IS_GEN(dev_priv, 2)) {
		if (INTEL_INFO(dev_priv)->num_pipes == 1) {
			dev_priv->display.update_wm = i845_update_wm;
			dev_priv->display.get_fifo_size = i845_get_fifo_size;
		} else {
			dev_priv->display.update_wm = i9xx_update_wm;
			dev_priv->display.get_fifo_size = i830_get_fifo_size;
		}
	} else {
		DRM_ERROR("unexpected fall-through in intel_init_pm\n");
	}
}