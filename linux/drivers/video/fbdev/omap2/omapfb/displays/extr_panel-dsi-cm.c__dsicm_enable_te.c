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
struct panel_drv_data {int /*<<< orphan*/  ext_te_gpio; struct omap_dss_device* in; } ;
struct TYPE_4__ {TYPE_1__* dsi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_te ) (struct omap_dss_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_SET_TEAR_OFF ; 
 int /*<<< orphan*/  MIPI_DCS_SET_TEAR_ON ; 
 int dsicm_dcs_write_0 (struct panel_drv_data*,int /*<<< orphan*/ ) ; 
 int dsicm_dcs_write_1 (struct panel_drv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int) ; 

__attribute__((used)) static int _dsicm_enable_te(struct panel_drv_data *ddata, bool enable)
{
	struct omap_dss_device *in = ddata->in;
	int r;

	if (enable)
		r = dsicm_dcs_write_1(ddata, MIPI_DCS_SET_TEAR_ON, 0);
	else
		r = dsicm_dcs_write_0(ddata, MIPI_DCS_SET_TEAR_OFF);

	if (!gpio_is_valid(ddata->ext_te_gpio))
		in->ops.dsi->enable_te(in, enable);

	/* possible panel bug */
	msleep(100);

	return r;
}