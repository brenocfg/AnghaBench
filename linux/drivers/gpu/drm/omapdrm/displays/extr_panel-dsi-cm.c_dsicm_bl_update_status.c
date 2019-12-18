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
struct panel_drv_data {int /*<<< orphan*/  lock; scalar_t__ enabled; TYPE_2__* pdev; struct omap_dss_device* src; } ;
struct omap_dss_device {TYPE_4__* ops; } ;
struct TYPE_5__ {scalar_t__ fb_blank; scalar_t__ power; int brightness; } ;
struct backlight_device {TYPE_1__ props; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* bus_unlock ) (struct omap_dss_device*) ;int /*<<< orphan*/  (* bus_lock ) (struct omap_dss_device*) ;} ;
struct TYPE_8__ {TYPE_3__ dsi; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCS_BRIGHTNESS ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct panel_drv_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int dsicm_dcs_write_1 (struct panel_drv_data*,int /*<<< orphan*/ ,int) ; 
 int dsicm_wake_up (struct panel_drv_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub2 (struct omap_dss_device*) ; 

__attribute__((used)) static int dsicm_bl_update_status(struct backlight_device *dev)
{
	struct panel_drv_data *ddata = dev_get_drvdata(&dev->dev);
	struct omap_dss_device *src = ddata->src;
	int r = 0;
	int level;

	if (dev->props.fb_blank == FB_BLANK_UNBLANK &&
			dev->props.power == FB_BLANK_UNBLANK)
		level = dev->props.brightness;
	else
		level = 0;

	dev_dbg(&ddata->pdev->dev, "update brightness to %d\n", level);

	mutex_lock(&ddata->lock);

	if (ddata->enabled) {
		src->ops->dsi.bus_lock(src);

		r = dsicm_wake_up(ddata);
		if (!r)
			r = dsicm_dcs_write_1(ddata, DCS_BRIGHTNESS, level);

		src->ops->dsi.bus_unlock(src);
	}

	mutex_unlock(&ddata->lock);

	return r;
}