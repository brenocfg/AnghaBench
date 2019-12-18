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
struct intel_dp {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int /*<<< orphan*/  output_format; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct drm_display_info {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  ycbcr_420_allowed; struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_FULLSCREEN ; 
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_YCBCR420 ; 
 int /*<<< orphan*/  drm_mode_is_420_only (struct drm_display_info const*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  intel_dp_get_colorimetry_status (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_pch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int skl_update_scaler_crtc (struct intel_crtc_state*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_dp_ycbcr420_config(struct intel_dp *intel_dp,
			 struct drm_connector *connector,
			 struct intel_crtc_state *crtc_state)
{
	const struct drm_display_info *info = &connector->display_info;
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	int ret;

	if (!drm_mode_is_420_only(info, adjusted_mode) ||
	    !intel_dp_get_colorimetry_status(intel_dp) ||
	    !connector->ycbcr_420_allowed)
		return 0;

	crtc_state->output_format = INTEL_OUTPUT_FORMAT_YCBCR420;

	/* YCBCR 420 output conversion needs a scaler */
	ret = skl_update_scaler_crtc(crtc_state);
	if (ret) {
		DRM_DEBUG_KMS("Scaler allocation for output failed\n");
		return ret;
	}

	intel_pch_panel_fitting(crtc, crtc_state, DRM_MODE_SCALE_FULLSCREEN);

	return 0;
}