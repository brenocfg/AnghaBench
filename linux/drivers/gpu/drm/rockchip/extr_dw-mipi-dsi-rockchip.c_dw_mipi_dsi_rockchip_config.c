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
struct dw_mipi_dsi_rockchip {TYPE_1__* cdata; int /*<<< orphan*/  grf_regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; scalar_t__ enable_grf_reg; int /*<<< orphan*/  lanecfg2; scalar_t__ lanecfg2_grf_reg; int /*<<< orphan*/  lanecfg1; scalar_t__ lanecfg1_grf_reg; int /*<<< orphan*/  lcdsel_big; int /*<<< orphan*/  lcdsel_lit; scalar_t__ lcdsel_grf_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_rockchip_config(struct dw_mipi_dsi_rockchip *dsi,
					int mux)
{
	if (dsi->cdata->lcdsel_grf_reg)
		regmap_write(dsi->grf_regmap, dsi->cdata->lcdsel_grf_reg,
			mux ? dsi->cdata->lcdsel_lit : dsi->cdata->lcdsel_big);

	if (dsi->cdata->lanecfg1_grf_reg)
		regmap_write(dsi->grf_regmap, dsi->cdata->lanecfg1_grf_reg,
					      dsi->cdata->lanecfg1);

	if (dsi->cdata->lanecfg2_grf_reg)
		regmap_write(dsi->grf_regmap, dsi->cdata->lanecfg2_grf_reg,
					      dsi->cdata->lanecfg2);

	if (dsi->cdata->enable_grf_reg)
		regmap_write(dsi->grf_regmap, dsi->cdata->enable_grf_reg,
					      dsi->cdata->enable);
}