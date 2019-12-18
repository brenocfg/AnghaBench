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
struct panel_drv_data {int /*<<< orphan*/  lock; scalar_t__ enabled; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* bus_lock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {TYPE_1__ dsi; } ;

/* Variables and functions */
 struct panel_drv_data* dev_get_drvdata (struct device*) ; 
 int dsicm_enter_ulps (struct panel_drv_data*) ; 
 int dsicm_wake_up (struct panel_drv_data*) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static ssize_t dsicm_store_ulps(struct device *dev,
		struct device_attribute *attr,
		const char *buf, size_t count)
{
	struct panel_drv_data *ddata = dev_get_drvdata(dev);
	struct omap_dss_device *src = ddata->src;
	unsigned long t;
	int r;

	r = kstrtoul(buf, 0, &t);
	if (r)
		return r;

	mutex_lock(&ddata->lock);

	if (ddata->enabled) {
		src->ops->dsi.bus_lock(src);

		if (t)
			r = dsicm_enter_ulps(ddata);
		else
			r = dsicm_wake_up(ddata);

		src->ops->dsi.bus_unlock(src);
	}

	mutex_unlock(&ddata->lock);

	if (r)
		return r;

	return count;
}