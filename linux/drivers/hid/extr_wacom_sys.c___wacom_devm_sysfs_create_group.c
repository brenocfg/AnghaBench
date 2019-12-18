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
struct wacom_sysfs_group_devres {struct kobject* root; struct attribute_group* group; } ;
struct wacom {TYPE_1__* hdev; } ;
struct kobject {int dummy; } ;
struct attribute_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ *,struct wacom_sysfs_group_devres*) ; 
 struct wacom_sysfs_group_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct wacom_sysfs_group_devres*) ; 
 int sysfs_create_group (struct kobject*,struct attribute_group*) ; 
 int /*<<< orphan*/  wacom_devm_sysfs_group_release ; 

__attribute__((used)) static int __wacom_devm_sysfs_create_group(struct wacom *wacom,
					   struct kobject *root,
					   struct attribute_group *group)
{
	struct wacom_sysfs_group_devres *devres;
	int error;

	devres = devres_alloc(wacom_devm_sysfs_group_release,
			      sizeof(struct wacom_sysfs_group_devres),
			      GFP_KERNEL);
	if (!devres)
		return -ENOMEM;

	devres->group = group;
	devres->root = root;

	error = sysfs_create_group(devres->root, group);
	if (error) {
		devres_free(devres);
		return error;
	}

	devres_add(&wacom->hdev->dev, devres);

	return 0;
}