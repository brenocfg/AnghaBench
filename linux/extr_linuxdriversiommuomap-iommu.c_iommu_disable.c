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
struct iommu_platform_data {int /*<<< orphan*/  reset_name; int /*<<< orphan*/  (* assert_reset ) (struct platform_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct iommu_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap2_iommu_disable (struct omap_iommu*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_disable(struct omap_iommu *obj)
{
	struct platform_device *pdev = to_platform_device(obj->dev);
	struct iommu_platform_data *pdata = dev_get_platdata(&pdev->dev);

	omap2_iommu_disable(obj);

	pm_runtime_put_sync(obj->dev);

	if (pdata && pdata->assert_reset)
		pdata->assert_reset(pdev, pdata->reset_name);
}