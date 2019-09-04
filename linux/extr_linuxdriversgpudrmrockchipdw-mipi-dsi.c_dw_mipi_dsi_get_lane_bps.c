#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dw_mipi_dsi {int lanes; unsigned long lane_mbps; unsigned int input_div; unsigned int feedback_div; int /*<<< orphan*/  pllref_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  format; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct TYPE_3__ {unsigned int max_mbps; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned long DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  MSEC_PER_SEC ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* dptdin_map ; 
 int mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_get_lane_bps(struct dw_mipi_dsi *dsi,
				    struct drm_display_mode *mode)
{
	unsigned int i, pre;
	unsigned long mpclk, pllref, tmp;
	unsigned int m = 1, n = 1, target_mbps = 1000;
	unsigned int max_mbps = dptdin_map[ARRAY_SIZE(dptdin_map) - 1].max_mbps;
	int bpp;

	bpp = mipi_dsi_pixel_format_to_bpp(dsi->format);
	if (bpp < 0) {
		DRM_DEV_ERROR(dsi->dev,
			      "failed to get bpp for pixel format %d\n",
			      dsi->format);
		return bpp;
	}

	mpclk = DIV_ROUND_UP(mode->clock, MSEC_PER_SEC);
	if (mpclk) {
		/* take 1 / 0.8, since mbps must big than bandwidth of RGB */
		tmp = mpclk * (bpp / dsi->lanes) * 10 / 8;
		if (tmp < max_mbps)
			target_mbps = tmp;
		else
			DRM_DEV_ERROR(dsi->dev,
				      "DPHY clock frequency is out of range\n");
	}

	pllref = DIV_ROUND_UP(clk_get_rate(dsi->pllref_clk), USEC_PER_SEC);
	tmp = pllref;

	/*
	 * The limits on the PLL divisor are:
	 *
	 *	5MHz <= (pllref / n) <= 40MHz
	 *
	 * we walk over these values in descreasing order so that if we hit
	 * an exact match for target_mbps it is more likely that "m" will be
	 * even.
	 *
	 * TODO: ensure that "m" is even after this loop.
	 */
	for (i = pllref / 5; i > (pllref / 40); i--) {
		pre = pllref / i;
		if ((tmp > (target_mbps % pre)) && (target_mbps / pre < 512)) {
			tmp = target_mbps % pre;
			n = i;
			m = target_mbps / pre;
		}
		if (tmp == 0)
			break;
	}

	dsi->lane_mbps = pllref / n * m;
	dsi->input_div = n;
	dsi->feedback_div = m;

	return 0;
}