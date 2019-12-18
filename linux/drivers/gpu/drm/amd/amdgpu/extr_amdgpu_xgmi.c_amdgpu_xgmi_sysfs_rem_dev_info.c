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
struct amdgpu_hive_info {int /*<<< orphan*/ * kobj; } ;
struct amdgpu_device {TYPE_1__* ddev; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {int /*<<< orphan*/  unique; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_xgmi_device_id ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_xgmi_sysfs_rem_dev_info(struct amdgpu_device *adev,
					  struct amdgpu_hive_info *hive)
{
	device_remove_file(adev->dev, &dev_attr_xgmi_device_id);
	sysfs_remove_link(&adev->dev->kobj, adev->ddev->unique);
	sysfs_remove_link(hive->kobj, adev->ddev->unique);
}