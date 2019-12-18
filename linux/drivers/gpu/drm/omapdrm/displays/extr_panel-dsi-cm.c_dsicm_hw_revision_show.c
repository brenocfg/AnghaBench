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
typedef  int u8 ;
struct panel_drv_data {int /*<<< orphan*/  lock; scalar_t__ enabled; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_2__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* bus_lock ) (struct omap_dss_device*) ;} ;
struct TYPE_4__ {TYPE_1__ dsi; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct panel_drv_data* dev_get_drvdata (struct device*) ; 
 int dsicm_get_id (struct panel_drv_data*,int*,int*,int*) ; 
 int dsicm_wake_up (struct panel_drv_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static ssize_t dsicm_hw_revision_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct panel_drv_data *ddata = dev_get_drvdata(dev);
	struct omap_dss_device *src = ddata->src;
	u8 id1, id2, id3;
	int r;

	mutex_lock(&ddata->lock);

	if (ddata->enabled) {
		src->ops->dsi.bus_lock(src);

		r = dsicm_wake_up(ddata);
		if (!r)
			r = dsicm_get_id(ddata, &id1, &id2, &id3);

		src->ops->dsi.bus_unlock(src);
	} else {
		r = -ENODEV;
	}

	mutex_unlock(&ddata->lock);

	if (r)
		return r;

	return snprintf(buf, PAGE_SIZE, "%02x.%02x.%02x\n", id1, id2, id3);
}