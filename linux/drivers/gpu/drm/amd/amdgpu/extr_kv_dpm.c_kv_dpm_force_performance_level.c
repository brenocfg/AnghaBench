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
struct TYPE_3__ {int forced_level; } ;
struct TYPE_4__ {TYPE_1__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_AUTO ; 
 int AMD_DPM_FORCED_LEVEL_HIGH ; 
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int kv_force_dpm_highest (struct amdgpu_device*) ; 
 int kv_force_dpm_lowest (struct amdgpu_device*) ; 
 int kv_unforce_levels (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_dpm_force_performance_level(void *handle,
					  enum amd_dpm_forced_level level)
{
	int ret;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	if (level == AMD_DPM_FORCED_LEVEL_HIGH) {
		ret = kv_force_dpm_highest(adev);
		if (ret)
			return ret;
	} else if (level == AMD_DPM_FORCED_LEVEL_LOW) {
		ret = kv_force_dpm_lowest(adev);
		if (ret)
			return ret;
	} else if (level == AMD_DPM_FORCED_LEVEL_AUTO) {
		ret = kv_unforce_levels(adev);
		if (ret)
			return ret;
	}

	adev->pm.dpm.forced_level = level;

	return 0;
}