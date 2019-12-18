#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdev_type {int dummy; } ;
struct mdev_parent {TYPE_1__* ops; int /*<<< orphan*/  unreg_sem; } ;
struct mdev_device {int /*<<< orphan*/  dev; struct mdev_parent* parent; int /*<<< orphan*/  type_kobj; } ;
struct TYPE_2__ {int (* remove ) (struct mdev_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_put_parent (struct mdev_parent*) ; 
 int /*<<< orphan*/  mdev_remove_sysfs_files (int /*<<< orphan*/ *,struct mdev_type*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int stub1 (struct mdev_device*) ; 
 struct mdev_type* to_mdev_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdev_device_remove_common(struct mdev_device *mdev)
{
	struct mdev_parent *parent;
	struct mdev_type *type;
	int ret;

	type = to_mdev_type(mdev->type_kobj);
	mdev_remove_sysfs_files(&mdev->dev, type);
	device_del(&mdev->dev);
	parent = mdev->parent;
	lockdep_assert_held(&parent->unreg_sem);
	ret = parent->ops->remove(mdev);
	if (ret)
		dev_err(&mdev->dev, "Remove failed: err=%d\n", ret);

	/* Balances with device_initialize() */
	put_device(&mdev->dev);
	mdev_put_parent(parent);
}