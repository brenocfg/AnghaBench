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
struct rockchip_hdmi {int /*<<< orphan*/  vpll_clk; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct rockchip_hdmi* to_rockchip_hdmi (struct drm_encoder*) ; 

__attribute__((used)) static void dw_hdmi_rockchip_encoder_mode_set(struct drm_encoder *encoder,
					      struct drm_display_mode *mode,
					      struct drm_display_mode *adj_mode)
{
	struct rockchip_hdmi *hdmi = to_rockchip_hdmi(encoder);

	clk_set_rate(hdmi->vpll_clk, adj_mode->clock * 1000);
}