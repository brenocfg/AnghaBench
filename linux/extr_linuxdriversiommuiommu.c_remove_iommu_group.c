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
struct iommu_ops {int /*<<< orphan*/  (* remove_device ) (struct device*) ;} ;
struct iommu_callback_data {struct iommu_ops* ops; } ;
struct device {scalar_t__ iommu_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct device*) ; 

__attribute__((used)) static int remove_iommu_group(struct device *dev, void *data)
{
	struct iommu_callback_data *cb = data;
	const struct iommu_ops *ops = cb->ops;

	if (ops->remove_device && dev->iommu_group)
		ops->remove_device(dev);

	return 0;
}