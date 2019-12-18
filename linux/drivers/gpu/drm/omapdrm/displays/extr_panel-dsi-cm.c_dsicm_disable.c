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
struct panel_drv_data {int /*<<< orphan*/  lock; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* bus_lock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {TYPE_1__ dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsicm_bl_power (struct panel_drv_data*,int) ; 
 int /*<<< orphan*/  dsicm_cancel_ulps_work (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_power_off (struct panel_drv_data*) ; 
 int dsicm_wake_up (struct panel_drv_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static void dsicm_disable(struct omap_dss_device *dssdev)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *src = ddata->src;
	int r;

	dsicm_bl_power(ddata, false);

	mutex_lock(&ddata->lock);

	dsicm_cancel_ulps_work(ddata);

	src->ops->dsi.bus_lock(src);

	r = dsicm_wake_up(ddata);
	if (!r)
		dsicm_power_off(ddata);

	src->ops->dsi.bus_unlock(src);

	mutex_unlock(&ddata->lock);
}