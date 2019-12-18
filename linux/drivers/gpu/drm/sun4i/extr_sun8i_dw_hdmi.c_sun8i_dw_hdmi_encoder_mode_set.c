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
struct sun8i_dw_hdmi {int /*<<< orphan*/  clk_tmds; TYPE_1__* quirks; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int crtc_clock; } ;
struct TYPE_2__ {scalar_t__ set_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct sun8i_dw_hdmi* encoder_to_sun8i_dw_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void sun8i_dw_hdmi_encoder_mode_set(struct drm_encoder *encoder,
					   struct drm_display_mode *mode,
					   struct drm_display_mode *adj_mode)
{
	struct sun8i_dw_hdmi *hdmi = encoder_to_sun8i_dw_hdmi(encoder);

	if (hdmi->quirks->set_rate)
		clk_set_rate(hdmi->clk_tmds, mode->crtc_clock * 1000);
}