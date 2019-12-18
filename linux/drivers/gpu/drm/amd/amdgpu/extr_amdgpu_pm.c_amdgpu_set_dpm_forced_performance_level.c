#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_device {scalar_t__ switch_power_state; struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_11__ {int forced_level; scalar_t__ thermal_active; } ;
struct TYPE_12__ {int /*<<< orphan*/  mutex; TYPE_5__ dpm; } ;
struct TYPE_10__ {TYPE_3__* pp_funcs; } ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct amdgpu_device {int flags; TYPE_6__ pm; TYPE_4__ powerplay; int /*<<< orphan*/  smu; TYPE_2__ virt; } ;
typedef  size_t ssize_t ;
typedef  enum amd_dpm_forced_level { ____Placeholder_amd_dpm_forced_level } amd_dpm_forced_level ;
struct TYPE_9__ {scalar_t__ force_performance_level; scalar_t__ get_performance_level; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* force_dpm_level ) (struct amdgpu_device*,int) ;} ;

/* Variables and functions */
 int AMD_DPM_FORCED_LEVEL_AUTO ; 
 int AMD_DPM_FORCED_LEVEL_HIGH ; 
 int AMD_DPM_FORCED_LEVEL_LOW ; 
 int AMD_DPM_FORCED_LEVEL_MANUAL ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_EXIT ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_PEAK ; 
 int AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD ; 
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 size_t EINVAL ; 
 scalar_t__ amdgim_is_hwperf (struct amdgpu_device*) ; 
 int amdgpu_dpm_force_performance_level (struct amdgpu_device*,int) ; 
 int amdgpu_dpm_get_performance_level (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int smu_force_performance_level (int /*<<< orphan*/ *,int) ; 
 int smu_get_performance_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int) ; 

__attribute__((used)) static ssize_t amdgpu_set_dpm_forced_performance_level(struct device *dev,
						       struct device_attribute *attr,
						       const char *buf,
						       size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	enum amd_dpm_forced_level level;
	enum amd_dpm_forced_level current_level = 0xff;
	int ret = 0;

	/* Can't force performance level when the card is off */
	if  ((adev->flags & AMD_IS_PX) &&
	     (ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	if (strncmp("low", buf, strlen("low")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_LOW;
	} else if (strncmp("high", buf, strlen("high")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_HIGH;
	} else if (strncmp("auto", buf, strlen("auto")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_AUTO;
	} else if (strncmp("manual", buf, strlen("manual")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_MANUAL;
	} else if (strncmp("profile_exit", buf, strlen("profile_exit")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_PROFILE_EXIT;
	} else if (strncmp("profile_standard", buf, strlen("profile_standard")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD;
	} else if (strncmp("profile_min_sclk", buf, strlen("profile_min_sclk")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK;
	} else if (strncmp("profile_min_mclk", buf, strlen("profile_min_mclk")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK;
	} else if (strncmp("profile_peak", buf, strlen("profile_peak")) == 0) {
		level = AMD_DPM_FORCED_LEVEL_PROFILE_PEAK;
	}  else {
		count = -EINVAL;
		goto fail;
	}

	/* handle sriov case here */
	if (amdgpu_sriov_vf(adev)) {
		if (amdgim_is_hwperf(adev) &&
		    adev->virt.ops->force_dpm_level) {
			mutex_lock(&adev->pm.mutex);
			adev->virt.ops->force_dpm_level(adev, level);
			mutex_unlock(&adev->pm.mutex);
			return count;
		} else {
			return -EINVAL;
		}
	}

	if (is_support_sw_smu(adev))
		current_level = smu_get_performance_level(&adev->smu);
	else if (adev->powerplay.pp_funcs->get_performance_level)
		current_level = amdgpu_dpm_get_performance_level(adev);

	if (current_level == level)
		return count;

	/* profile_exit setting is valid only when current mode is in profile mode */
	if (!(current_level & (AMD_DPM_FORCED_LEVEL_PROFILE_STANDARD |
	    AMD_DPM_FORCED_LEVEL_PROFILE_MIN_SCLK |
	    AMD_DPM_FORCED_LEVEL_PROFILE_MIN_MCLK |
	    AMD_DPM_FORCED_LEVEL_PROFILE_PEAK)) &&
	    (level == AMD_DPM_FORCED_LEVEL_PROFILE_EXIT)) {
		pr_err("Currently not in any profile mode!\n");
		return -EINVAL;
	}

	if (is_support_sw_smu(adev)) {
		ret = smu_force_performance_level(&adev->smu, level);
		if (ret)
			count = -EINVAL;
	} else if (adev->powerplay.pp_funcs->force_performance_level) {
		mutex_lock(&adev->pm.mutex);
		if (adev->pm.dpm.thermal_active) {
			count = -EINVAL;
			mutex_unlock(&adev->pm.mutex);
			goto fail;
		}
		ret = amdgpu_dpm_force_performance_level(adev, level);
		if (ret)
			count = -EINVAL;
		else
			adev->pm.dpm.forced_level = level;
		mutex_unlock(&adev->pm.mutex);
	}

fail:
	return count;
}