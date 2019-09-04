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
struct TYPE_4__ {int lck_div; int pck_div; } ;
struct TYPE_3__ {TYPE_2__ clock_info; } ;
struct dpi_data {TYPE_1__ mgr_config; int /*<<< orphan*/  dss; } ;
struct dpi_clk_calc_ctx {unsigned long fck; TYPE_2__ dispc_cinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int dpi_dss_clk_calc (struct dpi_data*,unsigned long,struct dpi_clk_calc_ctx*) ; 
 int dss_set_fck_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dpi_set_dispc_clk(struct dpi_data *dpi, unsigned long pck_req,
		unsigned long *fck, int *lck_div, int *pck_div)
{
	struct dpi_clk_calc_ctx ctx;
	int r;
	bool ok;

	ok = dpi_dss_clk_calc(dpi, pck_req, &ctx);
	if (!ok)
		return -EINVAL;

	r = dss_set_fck_rate(dpi->dss, ctx.fck);
	if (r)
		return r;

	dpi->mgr_config.clock_info = ctx.dispc_cinfo;

	*fck = ctx.fck;
	*lck_div = ctx.dispc_cinfo.lck_div;
	*pck_div = ctx.dispc_cinfo.pck_div;

	return 0;
}