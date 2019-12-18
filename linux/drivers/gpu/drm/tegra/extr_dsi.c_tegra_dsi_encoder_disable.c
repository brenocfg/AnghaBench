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
struct tegra_output {scalar_t__ panel; } ;
struct tegra_dsi {int /*<<< orphan*/  dev; } ;
struct tegra_dc {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int /*<<< orphan*/  DSI_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_unprepare (scalar_t__) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dsi_disable (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_soft_reset (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_unprepare (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_video_disable (struct tegra_dsi*) ; 
 int tegra_dsi_wait_idle (struct tegra_dsi*,int) ; 
 struct tegra_dsi* to_dsi (struct tegra_output*) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dc *dc = to_tegra_dc(encoder->crtc);
	struct tegra_dsi *dsi = to_dsi(output);
	u32 value;
	int err;

	if (output->panel)
		drm_panel_disable(output->panel);

	tegra_dsi_video_disable(dsi);

	/*
	 * The following accesses registers of the display controller, so make
	 * sure it's only executed when the output is attached to one.
	 */
	if (dc) {
		value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);
		value &= ~DSI_ENABLE;
		tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);

		tegra_dc_commit(dc);
	}

	err = tegra_dsi_wait_idle(dsi, 100);
	if (err < 0)
		dev_dbg(dsi->dev, "failed to idle DSI: %d\n", err);

	tegra_dsi_soft_reset(dsi);

	if (output->panel)
		drm_panel_unprepare(output->panel);

	tegra_dsi_disable(dsi);

	tegra_dsi_unprepare(dsi);
}