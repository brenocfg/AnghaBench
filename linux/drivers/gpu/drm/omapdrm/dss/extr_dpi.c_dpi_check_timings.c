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
struct omap_dss_device {int dummy; } ;
struct drm_display_mode {int hdisplay; int clock; } ;
struct dpi_data {scalar_t__ pll; } ;
struct TYPE_4__ {int lck_div; int pck_div; } ;
struct TYPE_3__ {unsigned long* clkout; } ;
struct dpi_clk_calc_ctx {size_t clkout_idx; unsigned long fck; TYPE_2__ dispc_cinfo; TYPE_1__ pll_cinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int dpi_dss_clk_calc (struct dpi_data*,int,struct dpi_clk_calc_ctx*) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int dpi_pll_clk_calc (struct dpi_data*,int,struct dpi_clk_calc_ctx*) ; 

__attribute__((used)) static int dpi_check_timings(struct omap_dss_device *dssdev,
			     struct drm_display_mode *mode)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	int lck_div, pck_div;
	unsigned long fck;
	unsigned long pck;
	struct dpi_clk_calc_ctx ctx;
	bool ok;

	if (mode->hdisplay % 8 != 0)
		return -EINVAL;

	if (mode->clock == 0)
		return -EINVAL;

	if (dpi->pll) {
		ok = dpi_pll_clk_calc(dpi, mode->clock * 1000, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.pll_cinfo.clkout[ctx.clkout_idx];
	} else {
		ok = dpi_dss_clk_calc(dpi, mode->clock * 1000, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.fck;
	}

	lck_div = ctx.dispc_cinfo.lck_div;
	pck_div = ctx.dispc_cinfo.pck_div;

	pck = fck / lck_div / pck_div;

	mode->clock = pck / 1000;

	return 0;
}