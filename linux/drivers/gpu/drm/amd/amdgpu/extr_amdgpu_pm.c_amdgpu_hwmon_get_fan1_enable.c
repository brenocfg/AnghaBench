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
typedef  scalar_t__ u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  get_fan_control_mode; } ;

/* Variables and functions */
 scalar_t__ AMD_FAN_CTRL_AUTO ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ amdgpu_dpm_get_fan_control_mode (struct amdgpu_device*) ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 scalar_t__ smu_get_fan_control_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_get_fan1_enable(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	u32 pwm_mode = 0;

	if (is_support_sw_smu(adev)) {
		pwm_mode = smu_get_fan_control_mode(&adev->smu);
	} else {
		if (!adev->powerplay.pp_funcs->get_fan_control_mode)
			return -EINVAL;

		pwm_mode = amdgpu_dpm_get_fan_control_mode(adev);
	}
	return sprintf(buf, "%i\n", pwm_mode == AMD_FAN_CTRL_AUTO ? 0 : 1);
}