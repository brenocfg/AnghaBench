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
struct zx_hdmi {int /*<<< orphan*/  xclk; int /*<<< orphan*/  osc_clk; int /*<<< orphan*/  cec_clk; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOU_HDMI ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct zx_hdmi* to_zx_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  vou_inf_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_hdmi_hw_enable (struct zx_hdmi*) ; 

__attribute__((used)) static void zx_hdmi_encoder_enable(struct drm_encoder *encoder)
{
	struct zx_hdmi *hdmi = to_zx_hdmi(encoder);

	clk_prepare_enable(hdmi->cec_clk);
	clk_prepare_enable(hdmi->osc_clk);
	clk_prepare_enable(hdmi->xclk);

	zx_hdmi_hw_enable(hdmi);

	vou_inf_enable(VOU_HDMI, encoder->crtc);
}