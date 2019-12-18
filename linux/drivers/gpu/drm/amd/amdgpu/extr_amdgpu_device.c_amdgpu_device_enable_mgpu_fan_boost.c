#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_gpu_instance {int mgpu_fan_enabled; struct amdgpu_device* adev; } ;
struct TYPE_5__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int flags; TYPE_2__ powerplay; } ;
struct TYPE_6__ {int num_dgpu; int /*<<< orphan*/  mutex; struct amdgpu_gpu_instance* gpu_ins; } ;
struct TYPE_4__ {scalar_t__ enable_mgpu_fan_boost; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int amdgpu_dpm_enable_mgpu_fan_boost (struct amdgpu_device*) ; 
 TYPE_3__ mgpu_info ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_device_enable_mgpu_fan_boost(void)
{
	struct amdgpu_gpu_instance *gpu_ins;
	struct amdgpu_device *adev;
	int i, ret = 0;

	mutex_lock(&mgpu_info.mutex);

	/*
	 * MGPU fan boost feature should be enabled
	 * only when there are two or more dGPUs in
	 * the system
	 */
	if (mgpu_info.num_dgpu < 2)
		goto out;

	for (i = 0; i < mgpu_info.num_dgpu; i++) {
		gpu_ins = &(mgpu_info.gpu_ins[i]);
		adev = gpu_ins->adev;
		if (!(adev->flags & AMD_IS_APU) &&
		    !gpu_ins->mgpu_fan_enabled &&
		    adev->powerplay.pp_funcs &&
		    adev->powerplay.pp_funcs->enable_mgpu_fan_boost) {
			ret = amdgpu_dpm_enable_mgpu_fan_boost(adev);
			if (ret)
				break;

			gpu_ins->mgpu_fan_enabled = 1;
		}
	}

out:
	mutex_unlock(&mgpu_info.mutex);

	return ret;
}