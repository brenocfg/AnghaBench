#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kset; } ;
struct iommu_group {int id; TYPE_1__ kobj; int /*<<< orphan*/  devices_kobj; int /*<<< orphan*/  notifier; int /*<<< orphan*/  devices; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 struct iommu_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iommu_group_attr_reserved_regions ; 
 int /*<<< orphan*/  iommu_group_attr_type ; 
 int iommu_group_create_file (struct iommu_group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_group_ida ; 
 int /*<<< orphan*/  iommu_group_kset ; 
 int /*<<< orphan*/  iommu_group_ktype ; 
 int /*<<< orphan*/  kfree (struct iommu_group*) ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,TYPE_1__*) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 struct iommu_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

struct iommu_group *iommu_group_alloc(void)
{
	struct iommu_group *group;
	int ret;

	group = kzalloc(sizeof(*group), GFP_KERNEL);
	if (!group)
		return ERR_PTR(-ENOMEM);

	group->kobj.kset = iommu_group_kset;
	mutex_init(&group->mutex);
	INIT_LIST_HEAD(&group->devices);
	BLOCKING_INIT_NOTIFIER_HEAD(&group->notifier);

	ret = ida_simple_get(&iommu_group_ida, 0, 0, GFP_KERNEL);
	if (ret < 0) {
		kfree(group);
		return ERR_PTR(ret);
	}
	group->id = ret;

	ret = kobject_init_and_add(&group->kobj, &iommu_group_ktype,
				   NULL, "%d", group->id);
	if (ret) {
		ida_simple_remove(&iommu_group_ida, group->id);
		kfree(group);
		return ERR_PTR(ret);
	}

	group->devices_kobj = kobject_create_and_add("devices", &group->kobj);
	if (!group->devices_kobj) {
		kobject_put(&group->kobj); /* triggers .release & free */
		return ERR_PTR(-ENOMEM);
	}

	/*
	 * The devices_kobj holds a reference on the group kobject, so
	 * as long as that exists so will the group.  We can therefore
	 * use the devices_kobj for reference counting.
	 */
	kobject_put(&group->kobj);

	ret = iommu_group_create_file(group,
				      &iommu_group_attr_reserved_regions);
	if (ret)
		return ERR_PTR(ret);

	ret = iommu_group_create_file(group, &iommu_group_attr_type);
	if (ret)
		return ERR_PTR(ret);

	pr_debug("Allocated group %d\n", group->id);

	return group;
}