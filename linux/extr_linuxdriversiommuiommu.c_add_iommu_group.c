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
struct iommu_ops {int (* add_device ) (struct device*) ;} ;
struct iommu_callback_data {struct iommu_ops* ops; } ;
struct device {int /*<<< orphan*/  iommu_group; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int stub1 (struct device*) ; 

__attribute__((used)) static int add_iommu_group(struct device *dev, void *data)
{
	struct iommu_callback_data *cb = data;
	const struct iommu_ops *ops = cb->ops;
	int ret;

	if (!ops->add_device)
		return 0;

	WARN_ON(dev->iommu_group);

	ret = ops->add_device(dev);

	/*
	 * We ignore -ENODEV errors for now, as they just mean that the
	 * device is not translated by an IOMMU. We still care about
	 * other errors and fail to initialize when they happen.
	 */
	if (ret == -ENODEV)
		ret = 0;

	return ret;
}