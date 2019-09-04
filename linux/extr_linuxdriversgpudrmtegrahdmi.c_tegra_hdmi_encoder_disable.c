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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_output {int dummy; } ;
struct tegra_hdmi {int /*<<< orphan*/  dev; scalar_t__ stereo; int /*<<< orphan*/  dvi; } ;
struct tegra_dc {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int /*<<< orphan*/  HDMI_ENABLE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_INT_ENABLE ; 
 int /*<<< orphan*/  HDMI_NV_PDISP_INT_MASK ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_disable_audio (struct tegra_hdmi*) ; 
 int /*<<< orphan*/  tegra_hdmi_disable_audio_infoframe (struct tegra_hdmi*) ; 
 int /*<<< orphan*/  tegra_hdmi_disable_avi_infoframe (struct tegra_hdmi*) ; 
 int /*<<< orphan*/  tegra_hdmi_disable_stereo_infoframe (struct tegra_hdmi*) ; 
 int /*<<< orphan*/  tegra_hdmi_writel (struct tegra_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_hdmi* to_hdmi (struct tegra_output*) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_hdmi_encoder_disable(struct drm_encoder *encoder)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dc *dc = to_tegra_dc(encoder->crtc);
	struct tegra_hdmi *hdmi = to_hdmi(output);
	u32 value;

	/*
	 * The following accesses registers of the display controller, so make
	 * sure it's only executed when the output is attached to one.
	 */
	if (dc) {
		value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);
		value &= ~HDMI_ENABLE;
		tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);

		tegra_dc_commit(dc);
	}

	if (!hdmi->dvi) {
		if (hdmi->stereo)
			tegra_hdmi_disable_stereo_infoframe(hdmi);

		tegra_hdmi_disable_audio_infoframe(hdmi);
		tegra_hdmi_disable_avi_infoframe(hdmi);
		tegra_hdmi_disable_audio(hdmi);
	}

	tegra_hdmi_writel(hdmi, 0, HDMI_NV_PDISP_INT_ENABLE);
	tegra_hdmi_writel(hdmi, 0, HDMI_NV_PDISP_INT_MASK);

	pm_runtime_put(hdmi->dev);
}