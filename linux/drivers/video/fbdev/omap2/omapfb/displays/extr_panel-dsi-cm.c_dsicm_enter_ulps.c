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
struct panel_drv_data {int ulps_enabled; TYPE_3__* pdev; int /*<<< orphan*/  ext_te_gpio; struct omap_dss_device* in; } ;
struct TYPE_5__ {TYPE_1__* dsi; } ;
struct omap_dss_device {TYPE_2__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (struct omap_dss_device*,int,int) ;} ;

/* Variables and functions */
 int _dsicm_enable_te (struct panel_drv_data*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsicm_cancel_ulps_work (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_panel_reset (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_queue_ulps_work (struct panel_drv_data*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,int,int) ; 

__attribute__((used)) static int dsicm_enter_ulps(struct panel_drv_data *ddata)
{
	struct omap_dss_device *in = ddata->in;
	int r;

	if (ddata->ulps_enabled)
		return 0;

	dsicm_cancel_ulps_work(ddata);

	r = _dsicm_enable_te(ddata, false);
	if (r)
		goto err;

	if (gpio_is_valid(ddata->ext_te_gpio))
		disable_irq(gpio_to_irq(ddata->ext_te_gpio));

	in->ops.dsi->disable(in, false, true);

	ddata->ulps_enabled = true;

	return 0;

err:
	dev_err(&ddata->pdev->dev, "enter ULPS failed");
	dsicm_panel_reset(ddata);

	ddata->ulps_enabled = false;

	dsicm_queue_ulps_work(ddata);

	return r;
}