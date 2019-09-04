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
struct zx_hdmi {int /*<<< orphan*/  cec_clk; int /*<<< orphan*/  osc_clk; int /*<<< orphan*/  xclk; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOU_HDMI ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct zx_hdmi* to_zx_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  vou_inf_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_hdmi_hw_disable (struct zx_hdmi*) ; 

__attribute__((used)) static void zx_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct zx_hdmi *hdmi = to_zx_hdmi(encoder);

	vou_inf_disable(VOU_HDMI, encoder->crtc);

	zx_hdmi_hw_disable(hdmi);

	clk_disable_unprepare(hdmi->xclk);
	clk_disable_unprepare(hdmi->osc_clk);
	clk_disable_unprepare(hdmi->cec_clk);
}