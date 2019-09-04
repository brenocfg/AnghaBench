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
struct gma_limit_t {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 size_t CDV_LIMIT_DAC_HDMI_27 ; 
 size_t CDV_LIMIT_DAC_HDMI_96 ; 
 size_t CDV_LIMIT_DP_100 ; 
 size_t CDV_LIMIT_DP_27 ; 
 size_t CDV_LIMIT_SINGLE_LVDS_100 ; 
 size_t CDV_LIMIT_SINGLE_LVDS_96 ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DISPLAYPORT ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  INTEL_OUTPUT_LVDS ; 
 struct gma_limit_t* cdv_intel_limits ; 
 scalar_t__ gma_pipe_has_type (struct drm_crtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct gma_limit_t *cdv_intel_limit(struct drm_crtc *crtc,
						 int refclk)
{
	const struct gma_limit_t *limit;
	if (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)) {
		/*
		 * Now only single-channel LVDS is supported on CDV. If it is
		 * incorrect, please add the dual-channel LVDS.
		 */
		if (refclk == 96000)
			limit = &cdv_intel_limits[CDV_LIMIT_SINGLE_LVDS_96];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_SINGLE_LVDS_100];
	} else if (gma_pipe_has_type(crtc, INTEL_OUTPUT_DISPLAYPORT) ||
			gma_pipe_has_type(crtc, INTEL_OUTPUT_EDP)) {
		if (refclk == 27000)
			limit = &cdv_intel_limits[CDV_LIMIT_DP_27];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_DP_100];
	} else {
		if (refclk == 27000)
			limit = &cdv_intel_limits[CDV_LIMIT_DAC_HDMI_27];
		else
			limit = &cdv_intel_limits[CDV_LIMIT_DAC_HDMI_96];
	}
	return limit;
}