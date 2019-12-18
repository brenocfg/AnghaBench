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
typedef  int u8 ;
struct intel_dvo_device {int dummy; } ;
struct drm_display_mode {int clock; int hdisplay; int vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7017_ACTIVE_INPUT_LINE_OUTPUT ; 
 int CH7017_CHARGE_PUMP_HIGH ; 
 int CH7017_CHARGE_PUMP_LOW ; 
 int /*<<< orphan*/  CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT ; 
 int /*<<< orphan*/  CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT ; 
 int CH7017_LOOP_FILTER_SHIFT ; 
 int CH7017_LVDS_CHANNEL_A ; 
 int CH7017_LVDS_CHANNEL_B ; 
 int /*<<< orphan*/  CH7017_LVDS_CONTROL_2 ; 
 int CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED ; 
 int /*<<< orphan*/  CH7017_LVDS_PLL_FEEDBACK_DIV ; 
 int CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT ; 
 int CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT ; 
 int CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT ; 
 int /*<<< orphan*/  CH7017_LVDS_PLL_VCO_CONTROL ; 
 int CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED ; 
 int CH7017_LVDS_PLL_VCO_SHIFT ; 
 int /*<<< orphan*/  CH7017_LVDS_POWER_DOWN ; 
 int CH7017_LVDS_POWER_DOWN_DEFAULT_RESERVED ; 
 int /*<<< orphan*/  CH7017_OUTPUTS_ENABLE ; 
 int CH7017_PHASE_DETECTOR_SHIFT ; 
 int /*<<< orphan*/  CH7017_VERTICAL_ACTIVE_LINE_OUTPUT ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  ch7017_dpms (struct intel_dvo_device*,int) ; 
 int /*<<< orphan*/  ch7017_dump_regs (struct intel_dvo_device*) ; 
 int /*<<< orphan*/  ch7017_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ch7017_mode_set(struct intel_dvo_device *dvo,
			    const struct drm_display_mode *mode,
			    const struct drm_display_mode *adjusted_mode)
{
	u8 lvds_pll_feedback_div, lvds_pll_vco_control;
	u8 outputs_enable, lvds_control_2, lvds_power_down;
	u8 horizontal_active_pixel_input;
	u8 horizontal_active_pixel_output, vertical_active_line_output;
	u8 active_input_line_output;

	DRM_DEBUG_KMS("Registers before mode setting\n");
	ch7017_dump_regs(dvo);

	/* LVDS PLL settings from page 75 of 7017-7017ds.pdf*/
	if (mode->clock < 100000) {
		outputs_enable = CH7017_LVDS_CHANNEL_A | CH7017_CHARGE_PUMP_LOW;
		lvds_pll_feedback_div = CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT) |
			(13 << CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT);
		lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_VCO_SHIFT) |
			(3 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		lvds_control_2 = (1 << CH7017_LOOP_FILTER_SHIFT) |
			(0 << CH7017_PHASE_DETECTOR_SHIFT);
	} else {
		outputs_enable = CH7017_LVDS_CHANNEL_A | CH7017_CHARGE_PUMP_HIGH;
		lvds_pll_feedback_div =
			CH7017_LVDS_PLL_FEEDBACK_DEFAULT_RESERVED |
			(2 << CH7017_LVDS_PLL_FEED_BACK_DIVIDER_SHIFT) |
			(3 << CH7017_LVDS_PLL_FEED_FORWARD_DIVIDER_SHIFT);
		lvds_control_2 = (3 << CH7017_LOOP_FILTER_SHIFT) |
			(0 << CH7017_PHASE_DETECTOR_SHIFT);
		if (1) { /* XXX: dual channel panel detection.  Assume yes for now. */
			outputs_enable |= CH7017_LVDS_CHANNEL_B;
			lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
				(2 << CH7017_LVDS_PLL_VCO_SHIFT) |
				(13 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		} else {
			lvds_pll_vco_control = CH7017_LVDS_PLL_VCO_DEFAULT_RESERVED |
				(1 << CH7017_LVDS_PLL_VCO_SHIFT) |
				(13 << CH7017_LVDS_PLL_POST_SCALE_DIV_SHIFT);
		}
	}

	horizontal_active_pixel_input = mode->hdisplay & 0x00ff;

	vertical_active_line_output = mode->vdisplay & 0x00ff;
	horizontal_active_pixel_output = mode->hdisplay & 0x00ff;

	active_input_line_output = ((mode->hdisplay & 0x0700) >> 8) |
				   (((mode->vdisplay & 0x0700) >> 8) << 3);

	lvds_power_down = CH7017_LVDS_POWER_DOWN_DEFAULT_RESERVED |
			  (mode->hdisplay & 0x0700) >> 8;

	ch7017_dpms(dvo, false);
	ch7017_write(dvo, CH7017_HORIZONTAL_ACTIVE_PIXEL_INPUT,
			horizontal_active_pixel_input);
	ch7017_write(dvo, CH7017_HORIZONTAL_ACTIVE_PIXEL_OUTPUT,
			horizontal_active_pixel_output);
	ch7017_write(dvo, CH7017_VERTICAL_ACTIVE_LINE_OUTPUT,
			vertical_active_line_output);
	ch7017_write(dvo, CH7017_ACTIVE_INPUT_LINE_OUTPUT,
			active_input_line_output);
	ch7017_write(dvo, CH7017_LVDS_PLL_VCO_CONTROL, lvds_pll_vco_control);
	ch7017_write(dvo, CH7017_LVDS_PLL_FEEDBACK_DIV, lvds_pll_feedback_div);
	ch7017_write(dvo, CH7017_LVDS_CONTROL_2, lvds_control_2);
	ch7017_write(dvo, CH7017_OUTPUTS_ENABLE, outputs_enable);

	/* Turn the LVDS back on with new settings. */
	ch7017_write(dvo, CH7017_LVDS_POWER_DOWN, lvds_power_down);

	DRM_DEBUG_KMS("Registers after mode setting\n");
	ch7017_dump_regs(dvo);
}