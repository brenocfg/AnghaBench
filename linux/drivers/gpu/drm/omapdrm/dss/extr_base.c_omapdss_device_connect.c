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
struct omap_dss_device {struct dss_device* dss; TYPE_1__* ops; scalar_t__ panel; scalar_t__ bridge; int /*<<< orphan*/  dev; } ;
struct dss_device {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* connect ) (struct omap_dss_device*,struct omap_dss_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ omapdss_device_is_connected (struct omap_dss_device*) ; 
 int stub1 (struct omap_dss_device*,struct omap_dss_device*) ; 

int omapdss_device_connect(struct dss_device *dss,
			   struct omap_dss_device *src,
			   struct omap_dss_device *dst)
{
	int ret;

	dev_dbg(&dss->pdev->dev, "connect(%s, %s)\n",
		src ? dev_name(src->dev) : "NULL",
		dst ? dev_name(dst->dev) : "NULL");

	if (!dst) {
		/*
		 * The destination is NULL when the source is connected to a
		 * bridge or panel instead of a DSS device. Stop here, we will
		 * attach the bridge or panel later when we will have a DRM
		 * encoder.
		 */
		return src && (src->bridge || src->panel) ? 0 : -EINVAL;
	}

	if (omapdss_device_is_connected(dst))
		return -EBUSY;

	dst->dss = dss;

	ret = dst->ops->connect(src, dst);
	if (ret < 0) {
		dst->dss = NULL;
		return ret;
	}

	return 0;
}