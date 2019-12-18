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
struct tegra_output {int /*<<< orphan*/  dev; } ;
struct tegra_dsi_state {int pclk; int mul; int div; int lanes; int bclk; int /*<<< orphan*/  period; int /*<<< orphan*/  timing; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  format; } ;
struct tegra_dsi {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  dev; int /*<<< orphan*/  format; } ;
struct tegra_dc {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc_state {TYPE_1__ mode; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (TYPE_1__*) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int mipi_dphy_timing_get_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mipi_dphy_timing_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tegra_dc_state_setup_clock (struct tegra_dc*,struct drm_crtc_state*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int tegra_dsi_get_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tegra_dsi_get_lanes (struct tegra_dsi*) ; 
 int tegra_dsi_get_muldiv (int /*<<< orphan*/ ,int*,int*) ; 
 struct tegra_dsi* to_dsi (struct tegra_output*) ; 
 struct tegra_dsi_state* to_dsi_state (struct drm_connector_state*) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_dsi_encoder_atomic_check(struct drm_encoder *encoder,
			       struct drm_crtc_state *crtc_state,
			       struct drm_connector_state *conn_state)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dsi_state *state = to_dsi_state(conn_state);
	struct tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	struct tegra_dsi *dsi = to_dsi(output);
	unsigned int scdiv;
	unsigned long plld;
	int err;

	state->pclk = crtc_state->mode.clock * 1000;

	err = tegra_dsi_get_muldiv(dsi->format, &state->mul, &state->div);
	if (err < 0)
		return err;

	state->lanes = tegra_dsi_get_lanes(dsi);

	err = tegra_dsi_get_format(dsi->format, &state->format);
	if (err < 0)
		return err;

	state->vrefresh = drm_mode_vrefresh(&crtc_state->mode);

	/* compute byte clock */
	state->bclk = (state->pclk * state->mul) / (state->div * state->lanes);

	DRM_DEBUG_KMS("mul: %u, div: %u, lanes: %u\n", state->mul, state->div,
		      state->lanes);
	DRM_DEBUG_KMS("format: %u, vrefresh: %u\n", state->format,
		      state->vrefresh);
	DRM_DEBUG_KMS("bclk: %lu\n", state->bclk);

	/*
	 * Compute bit clock and round up to the next MHz.
	 */
	plld = DIV_ROUND_UP(state->bclk * 8, USEC_PER_SEC) * USEC_PER_SEC;
	state->period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, plld);

	err = mipi_dphy_timing_get_default(&state->timing, state->period);
	if (err < 0)
		return err;

	err = mipi_dphy_timing_validate(&state->timing, state->period);
	if (err < 0) {
		dev_err(dsi->dev, "failed to validate D-PHY timing: %d\n", err);
		return err;
	}

	/*
	 * We divide the frequency by two here, but we make up for that by
	 * setting the shift clock divider (further below) to half of the
	 * correct value.
	 */
	plld /= 2;

	/*
	 * Derive pixel clock from bit clock using the shift clock divider.
	 * Note that this is only half of what we would expect, but we need
	 * that to make up for the fact that we divided the bit clock by a
	 * factor of two above.
	 *
	 * It's not clear exactly why this is necessary, but the display is
	 * not working properly otherwise. Perhaps the PLLs cannot generate
	 * frequencies sufficiently high.
	 */
	scdiv = ((8 * state->mul) / (state->div * state->lanes)) - 2;

	err = tegra_dc_state_setup_clock(dc, crtc_state, dsi->clk_parent,
					 plld, scdiv);
	if (err < 0) {
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		return err;
	}

	return err;
}