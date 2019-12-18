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
struct panel_drv_data {int te_enabled; int /*<<< orphan*/  lock; scalar_t__ enabled; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* bus_lock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {TYPE_1__ dsi; } ;

/* Variables and functions */
 int _dsicm_enable_te (struct panel_drv_data*,int) ; 
 int dsicm_wake_up (struct panel_drv_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub3 (struct omap_dss_device*) ; 
 struct panel_drv_data* to_panel_data (struct omap_dss_device*) ; 

__attribute__((used)) static int dsicm_enable_te(struct omap_dss_device *dssdev, bool enable)
{
	struct panel_drv_data *ddata = to_panel_data(dssdev);
	struct omap_dss_device *src = ddata->src;
	int r;

	mutex_lock(&ddata->lock);

	if (ddata->te_enabled == enable)
		goto end;

	src->ops->dsi.bus_lock(src);

	if (ddata->enabled) {
		r = dsicm_wake_up(ddata);
		if (r)
			goto err;

		r = _dsicm_enable_te(ddata, enable);
		if (r)
			goto err;
	}

	ddata->te_enabled = enable;

	src->ops->dsi.bus_unlock(src);
end:
	mutex_unlock(&ddata->lock);

	return 0;
err:
	src->ops->dsi.bus_unlock(src);
	mutex_unlock(&ddata->lock);

	return r;
}