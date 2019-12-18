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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int flags; TYPE_2__ powerplay; int /*<<< orphan*/  smu; TYPE_3__* ddev; } ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ switch_power_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  set_fan_control_mode; } ;

/* Variables and functions */
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_dpm_set_fan_control_mode (struct amdgpu_device*,int) ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int kstrtoint (char const*,int,int*) ; 
 int /*<<< orphan*/  smu_set_fan_control_mode (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_set_pwm1_enable(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf,
					    size_t count)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	int err;
	int value;

	/* Can't adjust fan when the card is off */
	if  ((adev->flags & AMD_IS_PX) &&
	     (adev->ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	err = kstrtoint(buf, 10, &value);
	if (err)
		return err;

	if (is_support_sw_smu(adev)) {
		smu_set_fan_control_mode(&adev->smu, value);
	} else {
		if (!adev->powerplay.pp_funcs->set_fan_control_mode)
			return -EINVAL;

		amdgpu_dpm_set_fan_control_mode(adev, value);
	}

	return count;
}