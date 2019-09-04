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
struct iommu_group {int /*<<< orphan*/  mutex; struct iommu_domain* default_domain; } ;
struct iommu_domain {scalar_t__ type; } ;
struct device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ IOMMU_DOMAIN_IDENTITY ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int __iommu_attach_group (struct iommu_domain*,struct iommu_group*) ; 
 struct iommu_domain* __iommu_domain_alloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 int iommu_group_device_count (struct iommu_group*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int iommu_request_dm_for_dev(struct device *dev)
{
	struct iommu_domain *dm_domain;
	struct iommu_group *group;
	int ret;

	/* Device must already be in a group before calling this function */
	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);

	mutex_lock(&group->mutex);

	/* Check if the default domain is already direct mapped */
	ret = 0;
	if (group->default_domain &&
	    group->default_domain->type == IOMMU_DOMAIN_IDENTITY)
		goto out;

	/* Don't change mappings of existing devices */
	ret = -EBUSY;
	if (iommu_group_device_count(group) != 1)
		goto out;

	/* Allocate a direct mapped domain */
	ret = -ENOMEM;
	dm_domain = __iommu_domain_alloc(dev->bus, IOMMU_DOMAIN_IDENTITY);
	if (!dm_domain)
		goto out;

	/* Attach the device to the domain */
	ret = __iommu_attach_group(dm_domain, group);
	if (ret) {
		iommu_domain_free(dm_domain);
		goto out;
	}

	/* Make the direct mapped domain the default for this group */
	if (group->default_domain)
		iommu_domain_free(group->default_domain);
	group->default_domain = dm_domain;

	pr_info("Using direct mapping for device %s\n", dev_name(dev));

	ret = 0;
out:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);

	return ret;
}