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
struct iommu_group {int /*<<< orphan*/  id; int /*<<< orphan*/  devices_kobj; int /*<<< orphan*/  mutex; int /*<<< orphan*/  notifier; scalar_t__ domain; int /*<<< orphan*/  devices; int /*<<< orphan*/  kobj; } ;
struct group_device {struct group_device* name; int /*<<< orphan*/  list; struct device* dev; } ;
struct device {int /*<<< orphan*/  kobj; struct iommu_group* iommu_group; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMMU_GROUP_NOTIFY_ADD_DEVICE ; 
 int __iommu_attach_device (scalar_t__,struct device*) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_create_direct_mappings (struct iommu_group*,struct device*) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  kfree (struct group_device*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 struct group_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int sysfs_create_link_nowarn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct group_device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_add_device_to_group (int /*<<< orphan*/ ,struct device*) ; 

int iommu_group_add_device(struct iommu_group *group, struct device *dev)
{
	int ret, i = 0;
	struct group_device *device;

	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device)
		return -ENOMEM;

	device->dev = dev;

	ret = sysfs_create_link(&dev->kobj, &group->kobj, "iommu_group");
	if (ret)
		goto err_free_device;

	device->name = kasprintf(GFP_KERNEL, "%s", kobject_name(&dev->kobj));
rename:
	if (!device->name) {
		ret = -ENOMEM;
		goto err_remove_link;
	}

	ret = sysfs_create_link_nowarn(group->devices_kobj,
				       &dev->kobj, device->name);
	if (ret) {
		if (ret == -EEXIST && i >= 0) {
			/*
			 * Account for the slim chance of collision
			 * and append an instance to the name.
			 */
			kfree(device->name);
			device->name = kasprintf(GFP_KERNEL, "%s.%d",
						 kobject_name(&dev->kobj), i++);
			goto rename;
		}
		goto err_free_name;
	}

	kobject_get(group->devices_kobj);

	dev->iommu_group = group;

	iommu_group_create_direct_mappings(group, dev);

	mutex_lock(&group->mutex);
	list_add_tail(&device->list, &group->devices);
	if (group->domain)
		ret = __iommu_attach_device(group->domain, dev);
	mutex_unlock(&group->mutex);
	if (ret)
		goto err_put_group;

	/* Notify any listeners about change to group. */
	blocking_notifier_call_chain(&group->notifier,
				     IOMMU_GROUP_NOTIFY_ADD_DEVICE, dev);

	trace_add_device_to_group(group->id, dev);

	dev_info(dev, "Adding to iommu group %d\n", group->id);

	return 0;

err_put_group:
	mutex_lock(&group->mutex);
	list_del(&device->list);
	mutex_unlock(&group->mutex);
	dev->iommu_group = NULL;
	kobject_put(group->devices_kobj);
err_free_name:
	kfree(device->name);
err_remove_link:
	sysfs_remove_link(&dev->kobj, "iommu_group");
err_free_device:
	kfree(device);
	dev_err(dev, "Failed to add to iommu group %d: %d\n", group->id, ret);
	return ret;
}