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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct device* vfio_mdev_get_iommu_device (struct device*) ; 

__attribute__((used)) static int vfio_mdev_iommu_device(struct device *dev, void *data)
{
	struct device **old = data, *new;

	new = vfio_mdev_get_iommu_device(dev);
	if (!new || (*old && *old != new))
		return -EINVAL;

	*old = new;

	return 0;
}