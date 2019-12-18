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
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOMMU_DEV_FEAT_AUX ; 
 int iommu_attach_device (struct iommu_domain*,struct device*) ; 
 int iommu_aux_attach_device (struct iommu_domain*,struct device*) ; 
 scalar_t__ iommu_dev_feature_enabled (struct device*,int /*<<< orphan*/ ) ; 
 struct device* vfio_mdev_get_iommu_device (struct device*) ; 

__attribute__((used)) static int vfio_mdev_attach_domain(struct device *dev, void *data)
{
	struct iommu_domain *domain = data;
	struct device *iommu_device;

	iommu_device = vfio_mdev_get_iommu_device(dev);
	if (iommu_device) {
		if (iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
			return iommu_aux_attach_device(domain, iommu_device);
		else
			return iommu_attach_device(domain, iommu_device);
	}

	return -EINVAL;
}