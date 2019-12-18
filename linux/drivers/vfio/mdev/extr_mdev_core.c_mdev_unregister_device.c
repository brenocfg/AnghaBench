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
struct mdev_parent {int /*<<< orphan*/  unreg_sem; int /*<<< orphan*/  next; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 struct mdev_parent* __find_parent_device (struct device*) ; 
 int /*<<< orphan*/  class_compat_remove_link (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_bus_compat_class ; 
 int /*<<< orphan*/  mdev_device_remove_cb ; 
 int /*<<< orphan*/  mdev_put_parent (struct mdev_parent*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_list_lock ; 
 int /*<<< orphan*/  parent_remove_sysfs_files (struct mdev_parent*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void mdev_unregister_device(struct device *dev)
{
	struct mdev_parent *parent;
	char *env_string = "MDEV_STATE=unregistered";
	char *envp[] = { env_string, NULL };

	mutex_lock(&parent_list_lock);
	parent = __find_parent_device(dev);

	if (!parent) {
		mutex_unlock(&parent_list_lock);
		return;
	}
	dev_info(dev, "MDEV: Unregistering\n");

	list_del(&parent->next);
	mutex_unlock(&parent_list_lock);

	down_write(&parent->unreg_sem);

	class_compat_remove_link(mdev_bus_compat_class, dev, NULL);

	device_for_each_child(dev, NULL, mdev_device_remove_cb);

	parent_remove_sysfs_files(parent);
	up_write(&parent->unreg_sem);

	mdev_put_parent(parent);

	/* We still have the caller's reference to use for the uevent */
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
}