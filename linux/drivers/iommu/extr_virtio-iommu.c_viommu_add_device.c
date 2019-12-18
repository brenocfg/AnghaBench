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
struct viommu_endpoint {int /*<<< orphan*/  resv_regions; struct viommu_dev* viommu; struct device* dev; } ;
struct viommu_dev {int /*<<< orphan*/  iommu; scalar_t__ probe_size; } ;
struct iommu_group {int dummy; } ;
struct iommu_fwspec {struct viommu_endpoint* iommu_priv; int /*<<< orphan*/  iommu_fwnode; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int PTR_ERR_OR_ZERO (struct iommu_group*) ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  kfree (struct viommu_endpoint*) ; 
 struct viommu_endpoint* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct viommu_dev* viommu_get_by_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viommu_ops ; 
 int viommu_probe_endpoint (struct viommu_dev*,struct device*) ; 
 int /*<<< orphan*/  viommu_put_resv_regions (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viommu_add_device(struct device *dev)
{
	int ret;
	struct iommu_group *group;
	struct viommu_endpoint *vdev;
	struct viommu_dev *viommu = NULL;
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	if (!fwspec || fwspec->ops != &viommu_ops)
		return -ENODEV;

	viommu = viommu_get_by_fwnode(fwspec->iommu_fwnode);
	if (!viommu)
		return -ENODEV;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev)
		return -ENOMEM;

	vdev->dev = dev;
	vdev->viommu = viommu;
	INIT_LIST_HEAD(&vdev->resv_regions);
	fwspec->iommu_priv = vdev;

	if (viommu->probe_size) {
		/* Get additional information for this endpoint */
		ret = viommu_probe_endpoint(viommu, dev);
		if (ret)
			goto err_free_dev;
	}

	ret = iommu_device_link(&viommu->iommu, dev);
	if (ret)
		goto err_free_dev;

	/*
	 * Last step creates a default domain and attaches to it. Everything
	 * must be ready.
	 */
	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group)) {
		ret = PTR_ERR(group);
		goto err_unlink_dev;
	}

	iommu_group_put(group);

	return PTR_ERR_OR_ZERO(group);

err_unlink_dev:
	iommu_device_unlink(&viommu->iommu, dev);
err_free_dev:
	viommu_put_resv_regions(dev, &vdev->resv_regions);
	kfree(vdev);

	return ret;
}