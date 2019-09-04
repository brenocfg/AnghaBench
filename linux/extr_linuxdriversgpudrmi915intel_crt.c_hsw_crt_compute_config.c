#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_display_mode {int flags; int crtc_hdisplay; int crtc_hblank_start; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_pch_encoder; int pipe_bpp; int port_clock; scalar_t__ bw_constrained; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_MODE_FLAG_DBLSCAN ; 
 scalar_t__ HAS_PCH_LPT (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_crt_compute_config(struct intel_encoder *encoder,
				   struct intel_crtc_state *pipe_config,
				   struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct drm_display_mode *adjusted_mode =
		&pipe_config->base.adjusted_mode;

	if (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		return false;

	/* HSW/BDW FDI limited to 4k */
	if (adjusted_mode->crtc_hdisplay > 4096 ||
	    adjusted_mode->crtc_hblank_start > 4096)
		return false;

	pipe_config->has_pch_encoder = true;

	/* LPT FDI RX only supports 8bpc. */
	if (HAS_PCH_LPT(dev_priv)) {
		if (pipe_config->bw_constrained && pipe_config->pipe_bpp < 24) {
			DRM_DEBUG_KMS("LPT only supports 24bpp\n");
			return false;
		}

		pipe_config->pipe_bpp = 24;
	}

	/* FDI must always be 2.7 GHz */
	pipe_config->port_clock = 135000 * 2;

	return true;
}