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
struct smu_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {scalar_t__ asic_type; } ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;

/* Variables and functions */
#define  AMD_DPM_FORCED_LEVEL_PROFILE_PEAK 128 
 scalar_t__ CHIP_NAVI10 ; 
 int EINVAL ; 
 int navi10_set_peak_clock_by_device (struct smu_context*) ; 

__attribute__((used)) static int navi10_set_performance_level(struct smu_context *smu, enum amd_dpm_forced_level level)
{
	int ret = 0;
	struct amdgpu_device *adev = smu->adev;

	if (adev->asic_type != CHIP_NAVI10)
		return -EINVAL;

	switch (level) {
	case AMD_DPM_FORCED_LEVEL_PROFILE_PEAK:
		ret = navi10_set_peak_clock_by_device(smu);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}