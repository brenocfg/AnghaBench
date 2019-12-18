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
struct tegra_rgb {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk; } ;
struct tegra_output {int /*<<< orphan*/  dev; } ;
struct tegra_dc {int dummy; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int clock; } ;
struct drm_crtc_state {TYPE_1__ mode; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tegra_output* encoder_to_output (struct drm_encoder*) ; 
 int tegra_dc_state_setup_clock (struct tegra_dc*,struct drm_crtc_state*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 struct tegra_rgb* to_rgb (struct tegra_output*) ; 
 struct tegra_dc* to_tegra_dc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_rgb_encoder_atomic_check(struct drm_encoder *encoder,
			       struct drm_crtc_state *crtc_state,
			       struct drm_connector_state *conn_state)
{
	struct tegra_output *output = encoder_to_output(encoder);
	struct tegra_dc *dc = to_tegra_dc(conn_state->crtc);
	unsigned long pclk = crtc_state->mode.clock * 1000;
	struct tegra_rgb *rgb = to_rgb(output);
	unsigned int div;
	int err;

	/*
	 * We may not want to change the frequency of the parent clock, since
	 * it may be a parent for other peripherals. This is due to the fact
	 * that on Tegra20 there's only a single clock dedicated to display
	 * (pll_d_out0), whereas later generations have a second one that can
	 * be used to independently drive a second output (pll_d2_out0).
	 *
	 * As a way to support multiple outputs on Tegra20 as well, pll_p is
	 * typically used as the parent clock for the display controllers.
	 * But this comes at a cost: pll_p is the parent of several other
	 * peripherals, so its frequency shouldn't change out of the blue.
	 *
	 * The best we can do at this point is to use the shift clock divider
	 * and hope that the desired frequency can be matched (or at least
	 * matched sufficiently close that the panel will still work).
	 */
	div = ((clk_get_rate(rgb->clk) * 2) / pclk) - 2;
	pclk = 0;

	err = tegra_dc_state_setup_clock(dc, crtc_state, rgb->clk_parent,
					 pclk, div);
	if (err < 0) {
		dev_err(output->dev, "failed to setup CRTC state: %d\n", err);
		return err;
	}

	return err;
}