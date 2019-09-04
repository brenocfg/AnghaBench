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
struct vc4_dsi_encoder {struct vc4_dsi* dsi; } ;
struct vc4_dsi {unsigned long divider; int /*<<< orphan*/  pll_phy_clock; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; int htotal; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  hsync_end; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 struct vc4_dsi_encoder* to_vc4_dsi_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool vc4_dsi_encoder_mode_fixup(struct drm_encoder *encoder,
				       const struct drm_display_mode *mode,
				       struct drm_display_mode *adjusted_mode)
{
	struct vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	struct vc4_dsi *dsi = vc4_encoder->dsi;
	struct clk *phy_parent = clk_get_parent(dsi->pll_phy_clock);
	unsigned long parent_rate = clk_get_rate(phy_parent);
	unsigned long pixel_clock_hz = mode->clock * 1000;
	unsigned long pll_clock = pixel_clock_hz * dsi->divider;
	int divider;

	/* Find what divider gets us a faster clock than the requested
	 * pixel clock.
	 */
	for (divider = 1; divider < 8; divider++) {
		if (parent_rate / divider < pll_clock) {
			divider--;
			break;
		}
	}

	/* Now that we've picked a PLL divider, calculate back to its
	 * pixel clock.
	 */
	pll_clock = parent_rate / divider;
	pixel_clock_hz = pll_clock / dsi->divider;

	adjusted_mode->clock = pixel_clock_hz / 1000;

	/* Given the new pixel clock, adjust HFP to keep vrefresh the same. */
	adjusted_mode->htotal = adjusted_mode->clock * mode->htotal /
				mode->clock;
	adjusted_mode->hsync_end += adjusted_mode->htotal - mode->htotal;
	adjusted_mode->hsync_start += adjusted_mode->htotal - mode->htotal;

	return true;
}