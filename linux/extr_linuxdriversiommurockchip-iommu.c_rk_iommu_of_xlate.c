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
struct rk_iommudata {int /*<<< orphan*/  iommu; } ;
struct platform_device {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct TYPE_2__ {struct rk_iommudata* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rk_iommudata* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_dev ; 
 struct platform_device* of_find_device_by_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rk_iommu_of_xlate(struct device *dev,
			     struct of_phandle_args *args)
{
	struct platform_device *iommu_dev;
	struct rk_iommudata *data;

	data = devm_kzalloc(dma_dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	iommu_dev = of_find_device_by_node(args->np);

	data->iommu = platform_get_drvdata(iommu_dev);
	dev->archdata.iommu = data;

	platform_device_put(iommu_dev);

	return 0;
}