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
struct qcom_iommu_dev {int /*<<< orphan*/  iommu; struct device* dev; } ;
struct iommu_group {int dummy; } ;
struct device_link {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_FLAG_PM_RUNTIME ; 
 int ENODEV ; 
 scalar_t__ IS_ERR_OR_NULL (struct iommu_group*) ; 
 int PTR_ERR_OR_ZERO (struct iommu_group*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device_link* device_link_add (struct device*,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 struct qcom_iommu_dev* to_iommu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_iommu_add_device(struct device *dev)
{
	struct qcom_iommu_dev *qcom_iommu = to_iommu(dev_iommu_fwspec_get(dev));
	struct iommu_group *group;
	struct device_link *link;

	if (!qcom_iommu)
		return -ENODEV;

	/*
	 * Establish the link between iommu and master, so that the
	 * iommu gets runtime enabled/disabled as per the master's
	 * needs.
	 */
	link = device_link_add(dev, qcom_iommu->dev, DL_FLAG_PM_RUNTIME);
	if (!link) {
		dev_err(qcom_iommu->dev, "Unable to create device link between %s and %s\n",
			dev_name(qcom_iommu->dev), dev_name(dev));
		return -ENODEV;
	}

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR_OR_NULL(group))
		return PTR_ERR_OR_ZERO(group);

	iommu_group_put(group);
	iommu_device_link(&qcom_iommu->iommu, dev);

	return 0;
}