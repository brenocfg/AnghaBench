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
typedef  int uint32_t ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct cdv_intel_dp {int /*<<< orphan*/  output_reg; } ;

/* Variables and functions */
 int DP_PORT_EN ; 
 int DRM_MODE_DPMS_ON ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdv_intel_dp_complete_link_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_link_down (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_dp_sink_dpms (struct gma_encoder*,int) ; 
 int /*<<< orphan*/  cdv_intel_dp_start_link_train (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_backlight_off (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_backlight_on (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_off (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_on (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_off (struct gma_encoder*) ; 
 int /*<<< orphan*/  cdv_intel_edp_panel_vdd_on (struct gma_encoder*) ; 
 int is_edp (struct gma_encoder*) ; 
 struct gma_encoder* to_gma_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void
cdv_intel_dp_dpms(struct drm_encoder *encoder, int mode)
{
	struct gma_encoder *intel_encoder = to_gma_encoder(encoder);
	struct cdv_intel_dp *intel_dp = intel_encoder->dev_priv;
	struct drm_device *dev = encoder->dev;
	uint32_t dp_reg = REG_READ(intel_dp->output_reg);
	int edp = is_edp(intel_encoder);

	if (mode != DRM_MODE_DPMS_ON) {
		if (edp) {
			cdv_intel_edp_backlight_off(intel_encoder);
			cdv_intel_edp_panel_vdd_on(intel_encoder);
		}
		cdv_intel_dp_sink_dpms(intel_encoder, mode);
		cdv_intel_dp_link_down(intel_encoder);
		if (edp) {
			cdv_intel_edp_panel_vdd_off(intel_encoder);
			cdv_intel_edp_panel_off(intel_encoder);
		}
	} else {
        	if (edp)
			cdv_intel_edp_panel_on(intel_encoder);
		cdv_intel_dp_sink_dpms(intel_encoder, mode);
		if (!(dp_reg & DP_PORT_EN)) {
			cdv_intel_dp_start_link_train(intel_encoder);
			cdv_intel_dp_complete_link_train(intel_encoder);
		}
		if (edp)
        		cdv_intel_edp_backlight_on(intel_encoder);
	}
}