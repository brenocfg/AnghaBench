#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mdev_parent {int /*<<< orphan*/  mdev_types_kset; TYPE_1__* ops; TYPE_2__* dev; int /*<<< orphan*/  type_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_attr_groups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int add_mdev_supported_type_groups (struct mdev_parent*) ; 
 int /*<<< orphan*/  kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ ) ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int parent_create_sysfs_files(struct mdev_parent *parent)
{
	int ret;

	parent->mdev_types_kset = kset_create_and_add("mdev_supported_types",
					       NULL, &parent->dev->kobj);

	if (!parent->mdev_types_kset)
		return -ENOMEM;

	INIT_LIST_HEAD(&parent->type_list);

	ret = sysfs_create_groups(&parent->dev->kobj,
				  parent->ops->dev_attr_groups);
	if (ret)
		goto create_err;

	ret = add_mdev_supported_type_groups(parent);
	if (ret)
		sysfs_remove_groups(&parent->dev->kobj,
				    parent->ops->dev_attr_groups);
	else
		return ret;

create_err:
	kset_unregister(parent->mdev_types_kset);
	return ret;
}