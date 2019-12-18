#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tegra_output {scalar_t__ panel; } ;
struct tegra_dsi_state {int period; int /*<<< orphan*/  timing; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  bclk; } ;
struct tegra_dsi {int dummy; } ;
struct tegra_dc {int /*<<< orphan*/  pipe; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DISP_DISP_WIN_OPTIONS ; 
 int /*<<< orphan*/  DSI_ENABLE ; 
 int /*<<< orphan*/  drm_panel_enable (scalar_t__) ; 
 int /*<<< orphan*/  drm_panel_prepare (scalar_t__) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dsi_configure (struct tegra_dsi*,int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 int /*<<< orphan*/  tegra_dsi_enable (struct tegra_dsi*) ; 
 struct tegra_dsi_state* tegra_dsi_get_state (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_prepare (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_set_phy_timing (struct tegra_dsi*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_dsi_set_timeout (struct tegra_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_dsi* to_dsi (struct tegra_output*) ; 
 struct tegra_dc* to_tegra_dc (TYPE_2__*) ; 

__attribute__((used)) static void tegra_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dc *dc = to_tegra_dc(encoder->crtc);
	struct tegra_dsi *dsi = to_dsi(output);
	struct tegra_dsi_state *state;
	u32 value;

	tegra_dsi_prepare(dsi);

	state = tegra_dsi_get_state(dsi);

	tegra_dsi_set_timeout(dsi, state->bclk, state->vrefresh);

	/*
	 * The D-PHY timing fields are expressed in byte-clock cycles, so
	 * multiply the period by 8.
	 */
	tegra_dsi_set_phy_timing(dsi, state->period * 8, &state->timing);

	if (output->panel)
		drm_panel_prepare(output->panel);

	tegra_dsi_configure(dsi, dc->pipe, mode);

	/* enable display controller */
	value = tegra_dc_readl(dc, DC_DISP_DISP_WIN_OPTIONS);
	value |= DSI_ENABLE;
	tegra_dc_writel(dc, value, DC_DISP_DISP_WIN_OPTIONS);

	tegra_dc_commit(dc);

	/* enable DSI controller */
	tegra_dsi_enable(dsi);

	if (output->panel)
		drm_panel_enable(output->panel);
}