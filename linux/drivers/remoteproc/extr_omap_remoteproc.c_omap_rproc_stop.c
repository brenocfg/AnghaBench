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
struct TYPE_3__ {struct device* parent; } ;
struct rproc {struct omap_rproc* priv; TYPE_1__ dev; } ;
struct TYPE_4__ {struct omap_rproc_pdata* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct omap_rproc_pdata {int (* device_shutdown ) (struct platform_device*) ;} ;
struct omap_rproc {int /*<<< orphan*/  mbox; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int omap_rproc_stop(struct rproc *rproc)
{
	struct device *dev = rproc->dev.parent;
	struct platform_device *pdev = to_platform_device(dev);
	struct omap_rproc_pdata *pdata = pdev->dev.platform_data;
	struct omap_rproc *oproc = rproc->priv;
	int ret;

	ret = pdata->device_shutdown(pdev);
	if (ret)
		return ret;

	mbox_free_channel(oproc->mbox);

	return 0;
}