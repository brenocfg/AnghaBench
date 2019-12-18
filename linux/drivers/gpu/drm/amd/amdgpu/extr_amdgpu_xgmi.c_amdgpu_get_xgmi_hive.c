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
struct amdgpu_hive_info {scalar_t__ hive_id; int pstate; int /*<<< orphan*/  hive_lock; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  device_list; struct amdgpu_device* adev; } ;
struct TYPE_3__ {scalar_t__ hive_id; } ;
struct TYPE_4__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {TYPE_2__ gmc; } ;

/* Variables and functions */
 int AMDGPU_MAX_XGMI_HIVE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_xgmi_sysfs_create (struct amdgpu_device*,struct amdgpu_hive_info*) ; 
 int hive_count ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct amdgpu_hive_info* xgmi_hives ; 
 int /*<<< orphan*/  xgmi_mutex ; 

struct amdgpu_hive_info *amdgpu_get_xgmi_hive(struct amdgpu_device *adev, int lock)
{
	int i;
	struct amdgpu_hive_info *tmp;

	if (!adev->gmc.xgmi.hive_id)
		return NULL;

	mutex_lock(&xgmi_mutex);

	for (i = 0 ; i < hive_count; ++i) {
		tmp = &xgmi_hives[i];
		if (tmp->hive_id == adev->gmc.xgmi.hive_id) {
			if (lock)
				mutex_lock(&tmp->hive_lock);
			mutex_unlock(&xgmi_mutex);
			return tmp;
		}
	}
	if (i >= AMDGPU_MAX_XGMI_HIVE) {
		mutex_unlock(&xgmi_mutex);
		return NULL;
	}

	/* initialize new hive if not exist */
	tmp = &xgmi_hives[hive_count++];

	if (amdgpu_xgmi_sysfs_create(adev, tmp)) {
		mutex_unlock(&xgmi_mutex);
		return NULL;
	}

	tmp->adev = adev;
	tmp->hive_id = adev->gmc.xgmi.hive_id;
	INIT_LIST_HEAD(&tmp->device_list);
	mutex_init(&tmp->hive_lock);
	mutex_init(&tmp->reset_lock);

	if (lock)
		mutex_lock(&tmp->hive_lock);
	tmp->pstate = -1;
	mutex_unlock(&xgmi_mutex);

	return tmp;
}