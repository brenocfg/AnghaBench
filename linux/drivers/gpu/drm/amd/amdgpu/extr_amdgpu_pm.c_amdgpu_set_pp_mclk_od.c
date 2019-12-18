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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  boot_ps; int /*<<< orphan*/  current_ps; } ;
struct TYPE_8__ {TYPE_3__ dpm; } ;
struct TYPE_6__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_4__ pm; TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  size_t ssize_t ;
struct TYPE_5__ {scalar_t__ dispatch_tasks; scalar_t__ set_mclk_od; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_READJUST_POWER_STATE ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  SMU_OD_MCLK ; 
 int /*<<< orphan*/  amdgpu_dpm_dispatch_task (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_dpm_set_mclk_od (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_pm_compute_clocks (struct amdgpu_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 long smu_set_od_percentage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t amdgpu_set_pp_mclk_od(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct amdgpu_device *adev = ddev->dev_private;
	int ret;
	long int value;

	ret = kstrtol(buf, 0, &value);

	if (ret) {
		count = -EINVAL;
		goto fail;
	}

	if (is_support_sw_smu(adev)) {
		value = smu_set_od_percentage(&(adev->smu), SMU_OD_MCLK, (uint32_t)value);
	} else {
		if (adev->powerplay.pp_funcs->set_mclk_od)
			amdgpu_dpm_set_mclk_od(adev, (uint32_t)value);

		if (adev->powerplay.pp_funcs->dispatch_tasks) {
			amdgpu_dpm_dispatch_task(adev, AMD_PP_TASK_READJUST_POWER_STATE, NULL);
		} else {
			adev->pm.dpm.current_ps = adev->pm.dpm.boot_ps;
			amdgpu_pm_compute_clocks(adev);
		}
	}

fail:
	return count;
}