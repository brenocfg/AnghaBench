#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct videomode {int hactive; unsigned long pixelclock; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_5__ {int dispc_channel; } ;
struct dpi_data {scalar_t__ pll; TYPE_2__* dss; TYPE_1__ output; } ;
struct TYPE_8__ {int lck_div; int pck_div; } ;
struct TYPE_7__ {unsigned long* clkout; } ;
struct dpi_clk_calc_ctx {size_t clkout_idx; unsigned long fck; TYPE_4__ dispc_cinfo; TYPE_3__ pll_cinfo; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_6__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dispc_mgr_timings_ok (int /*<<< orphan*/ ,int,struct videomode*) ; 
 int dpi_dss_clk_calc (struct dpi_data*,unsigned long,struct dpi_clk_calc_ctx*) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int dpi_pll_clk_calc (struct dpi_data*,unsigned long,struct dpi_clk_calc_ctx*) ; 

__attribute__((used)) static int dpi_check_timings(struct omap_dss_device *dssdev,
			     struct videomode *vm)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	enum omap_channel channel = dpi->output.dispc_channel;
	int lck_div, pck_div;
	unsigned long fck;
	unsigned long pck;
	struct dpi_clk_calc_ctx ctx;
	bool ok;

	if (vm->hactive % 8 != 0)
		return -EINVAL;

	if (!dispc_mgr_timings_ok(dpi->dss->dispc, channel, vm))
		return -EINVAL;

	if (vm->pixelclock == 0)
		return -EINVAL;

	if (dpi->pll) {
		ok = dpi_pll_clk_calc(dpi, vm->pixelclock, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.pll_cinfo.clkout[ctx.clkout_idx];
	} else {
		ok = dpi_dss_clk_calc(dpi, vm->pixelclock, &ctx);
		if (!ok)
			return -EINVAL;

		fck = ctx.fck;
	}

	lck_div = ctx.dispc_cinfo.lck_div;
	pck_div = ctx.dispc_cinfo.pck_div;

	pck = fck / lck_div / pck_div;

	vm->pixelclock = pck;

	return 0;
}