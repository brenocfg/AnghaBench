#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct device {TYPE_1__* iommu_fwspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 struct platform_device* of_find_device_by_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ipmmu_init_platform_device(struct device *dev,
				      struct of_phandle_args *args)
{
	struct platform_device *ipmmu_pdev;

	ipmmu_pdev = of_find_device_by_node(args->np);
	if (!ipmmu_pdev)
		return -ENODEV;

	dev->iommu_fwspec->iommu_priv = platform_get_drvdata(ipmmu_pdev);
	return 0;
}