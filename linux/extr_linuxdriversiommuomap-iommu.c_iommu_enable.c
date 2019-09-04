#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_iommu {int /*<<< orphan*/  dev; } ;
struct iommu_platform_data {int (* deassert_reset ) (struct platform_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  reset_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct iommu_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int omap2_iommu_enable (struct omap_iommu*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iommu_enable(struct omap_iommu *obj)
{
	int err;
	struct platform_device *pdev = to_platform_device(obj->dev);
	struct iommu_platform_data *pdata = dev_get_platdata(&pdev->dev);

	if (pdata && pdata->deassert_reset) {
		err = pdata->deassert_reset(pdev, pdata->reset_name);
		if (err) {
			dev_err(obj->dev, "deassert_reset failed: %d\n", err);
			return err;
		}
	}

	pm_runtime_get_sync(obj->dev);

	err = omap2_iommu_enable(obj);

	return err;
}