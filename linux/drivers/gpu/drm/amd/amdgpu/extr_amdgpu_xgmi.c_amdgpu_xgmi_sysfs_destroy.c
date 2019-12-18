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
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;
struct amdgpu_hive_info {int /*<<< orphan*/ * kobj; TYPE_1__ dev_attr; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_xgmi_sysfs_destroy(struct amdgpu_device *adev,
				    struct amdgpu_hive_info *hive)
{
	sysfs_remove_file(hive->kobj, &hive->dev_attr.attr);
	kobject_del(hive->kobj);
	kobject_put(hive->kobj);
	hive->kobj = NULL;
}