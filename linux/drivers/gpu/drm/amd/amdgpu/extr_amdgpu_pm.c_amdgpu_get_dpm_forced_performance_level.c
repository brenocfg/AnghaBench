#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {scalar_t__ switch_power_state; struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int forced_level; } ;
struct TYPE_8__ {TYPE_3__ dpm; } ;
struct TYPE_6__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int flags; TYPE_4__ pm; TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_5__ {scalar_t__ get_performance_level; } ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_AUTO ; 
 int AMD_DPM_FORCED_LEVEL_HIGH ; 
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int AMD_DPM_FORCED_LEVEL_MANUAL ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD ; 
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_dpm_get_performance_level (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_get_performance_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t amdgpu_get_dpm_forced_performance_level(struct device *dev,
						struct device_attribute *attr,
								char *buf)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	enum amd_dpm_forced_level level = 0xff;

	if (amdgpu_sriov_vf(adev))
		return 0;

	if ((adev->flags & AMD_IS_PX) &&
	    (ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return snprintf(buf, PAGE_SIZE, "off\n");

	if (is_support_sw_smu(adev))
		level = smu_get_performance_level(&adev->smu);
	else if (adev->powerplay.pp_funcs->get_performance_level)
		level = amdgpu_dpm_get_performance_level(adev);
	else
		level = adev->pm.dpm.forced_level;

	return snprintf(buf, PAGE_SIZE, "%s\n",
			(level == AMD_DPM_FORCED_LEVEL_AUTO) ? "auto" :
			(level == AMD_DPM_FORCED_LEVEL_LOW) ? "low" :
			(level == AMD_DPM_FORCED_LEVEL_HIGH) ? "high" :
			(level == AMD_DPM_FORCED_LEVEL_MANUAL) ? "manual" :
			(level == AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD) ? "profile_standard" :
			(level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK) ? "profile_min_sclk" :
			(level == AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK) ? "profile_min_mclk" :
			(level == AMD_DPM_FORCED_LEVEL_PROFILE_PEAK) ? "profile_peak" :
			"unknown");
}