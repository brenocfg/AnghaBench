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
struct amdgpu_hive_info {int /*<<< orphan*/  hive_lock; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  number_devices; } ;
struct TYPE_3__ {int /*<<< orphan*/  supported; } ;
struct TYPE_4__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {TYPE_2__ gmc; } ;

/* Variables and functions */
 struct amdgpu_hive_info* amdgpu_get_xgmi_hive (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_xgmi_sysfs_destroy (struct amdgpu_device*,struct amdgpu_hive_info*) ; 
 int /*<<< orphan*/  amdgpu_xgmi_sysfs_rem_dev_info (struct amdgpu_device*,struct amdgpu_hive_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_xgmi_remove_device(struct amdgpu_device *adev)
{
	struct amdgpu_hive_info *hive;

	if (!adev->gmc.xgmi.supported)
		return;

	hive = amdgpu_get_xgmi_hive(adev, 1);
	if (!hive)
		return;

	if (!(hive->number_devices--)) {
		amdgpu_xgmi_sysfs_destroy(adev, hive);
		mutex_destroy(&hive->hive_lock);
		mutex_destroy(&hive->reset_lock);
	} else {
		amdgpu_xgmi_sysfs_rem_dev_info(adev, hive);
		mutex_unlock(&hive->hive_lock);
	}
}