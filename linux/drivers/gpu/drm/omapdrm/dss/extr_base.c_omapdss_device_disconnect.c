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
struct omap_dss_device {scalar_t__ state; struct dss_device* dss; TYPE_2__* ops; int /*<<< orphan*/  display; int /*<<< orphan*/  id; int /*<<< orphan*/  panel; int /*<<< orphan*/  bridge; int /*<<< orphan*/  dev; } ;
struct dss_device {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disconnect ) (struct omap_dss_device*,struct omap_dss_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_DISPLAY_DISABLED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapdss_device_is_connected (struct omap_dss_device*) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 

void omapdss_device_disconnect(struct omap_dss_device *src,
			       struct omap_dss_device *dst)
{
	struct dss_device *dss = src ? src->dss : dst->dss;

	dev_dbg(&dss->pdev->dev, "disconnect(%s, %s)\n",
		src ? dev_name(src->dev) : "NULL",
		dst ? dev_name(dst->dev) : "NULL");

	if (!dst) {
		WARN_ON(!src->bridge && !src->panel);
		return;
	}

	if (!dst->id && !omapdss_device_is_connected(dst)) {
		WARN_ON(!dst->display);
		return;
	}

	WARN_ON(dst->state != OMAP_DSS_DISPLAY_DISABLED);

	dst->ops->disconnect(src, dst);
	dst->dss = NULL;
}