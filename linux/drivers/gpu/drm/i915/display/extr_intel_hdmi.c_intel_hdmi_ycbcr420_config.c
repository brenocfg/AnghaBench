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
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int port_clock; int /*<<< orphan*/  output_format; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  ycbcr_420_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_SCALE_FULLSCREEN ; 
 int /*<<< orphan*/  INTEL_OUTPUT_FORMAT_YCBCR420 ; 
 int /*<<< orphan*/  intel_pch_panel_fitting (struct intel_crtc*,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ skl_update_scaler_crtc (struct intel_crtc_state*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_hdmi_ycbcr420_config(struct drm_connector *connector,
			   struct intel_crtc_state *config,
			   int *clock_12bpc, int *clock_10bpc,
			   int *clock_8bpc)
{
	struct intel_crtc *intel_crtc = to_intel_crtc(config->base.crtc);

	if (!connector->ycbcr_420_allowed) {
		DRM_ERROR("Platform doesn't support YCBCR420 output\n");
		return false;
	}

	/* YCBCR420 TMDS rate requirement is half the pixel clock */
	config->port_clock /= 2;
	*clock_12bpc /= 2;
	*clock_10bpc /= 2;
	*clock_8bpc /= 2;
	config->output_format = INTEL_OUTPUT_FORMAT_YCBCR420;

	/* YCBCR 420 output conversion needs a scaler */
	if (skl_update_scaler_crtc(config)) {
		DRM_DEBUG_KMS("Scaler allocation for output failed\n");
		return false;
	}

	intel_pch_panel_fitting(intel_crtc, config,
				DRM_MODE_SCALE_FULLSCREEN);

	return true;
}