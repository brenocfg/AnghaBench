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
struct device {TYPE_1__* driver; } ;
struct platform_device {struct device dev; } ;
struct fimc_md {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
#define  IDX_CSIS 131 
#define  IDX_FIMC 130 
#define  IDX_FLITE 129 
#define  IDX_IS_ISP 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int register_csis_entity (struct fimc_md*,struct platform_device*,void*) ; 
 int register_fimc_entity (struct fimc_md*,void*) ; 
 int register_fimc_is_entity (struct fimc_md*,void*) ; 
 int register_fimc_lite_entity (struct fimc_md*,void*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_md_register_platform_entity(struct fimc_md *fmd,
					    struct platform_device *pdev,
					    int plat_entity)
{
	struct device *dev = &pdev->dev;
	int ret = -EPROBE_DEFER;
	void *drvdata;

	/* Lock to ensure dev->driver won't change. */
	device_lock(dev);

	if (!dev->driver || !try_module_get(dev->driver->owner))
		goto dev_unlock;

	drvdata = dev_get_drvdata(dev);
	/* Some subdev didn't probe successfully id drvdata is NULL */
	if (drvdata) {
		switch (plat_entity) {
		case IDX_FIMC:
			ret = register_fimc_entity(fmd, drvdata);
			break;
		case IDX_FLITE:
			ret = register_fimc_lite_entity(fmd, drvdata);
			break;
		case IDX_CSIS:
			ret = register_csis_entity(fmd, pdev, drvdata);
			break;
		case IDX_IS_ISP:
			ret = register_fimc_is_entity(fmd, drvdata);
			break;
		default:
			ret = -ENODEV;
		}
	}

	module_put(dev->driver->owner);
dev_unlock:
	device_unlock(dev);
	if (ret == -EPROBE_DEFER)
		dev_info(&fmd->pdev->dev, "deferring %s device registration\n",
			dev_name(dev));
	else if (ret < 0)
		dev_err(&fmd->pdev->dev, "%s device registration failed (%d)\n",
			dev_name(dev), ret);
	return ret;
}