#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct panel_drv_data {scalar_t__ enabled; scalar_t__ vpnl; scalar_t__ vddi; TYPE_1__* pdev; int /*<<< orphan*/  channel; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disable ) (struct omap_dss_device*,int,int) ;int /*<<< orphan*/  (* disable_video_output ) (struct omap_dss_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_3__ dsi; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dsicm_dcs_write_0 (struct panel_drv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsicm_hw_reset (struct panel_drv_data*) ; 
 int dsicm_sleep_in (struct panel_drv_data*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*,int,int) ; 

__attribute__((used)) static void dsicm_power_off(struct panel_drv_data *ddata)
{
	struct omap_dss_device *src = ddata->src;
	int r;

	src->ops->dsi.disable_video_output(src, ddata->channel);

	r = dsicm_dcs_write_0(ddata, MIPI_DCS_SET_DISPLAY_OFF);
	if (!r)
		r = dsicm_sleep_in(ddata);

	if (r) {
		dev_err(&ddata->pdev->dev,
				"error disabling panel, issuing HW reset\n");
		dsicm_hw_reset(ddata);
	}

	src->ops->dsi.disable(src, true, false);

	if (ddata->vddi)
		regulator_disable(ddata->vddi);
	if (ddata->vpnl)
		regulator_disable(ddata->vpnl);

	ddata->enabled = 0;
}