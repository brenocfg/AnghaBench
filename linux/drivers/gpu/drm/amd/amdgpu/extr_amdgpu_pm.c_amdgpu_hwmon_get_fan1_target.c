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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* pp_funcs; } ;
struct amdgpu_device {int flags; TYPE_2__ powerplay; int /*<<< orphan*/  smu; TYPE_3__* ddev; } ;
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ switch_power_state; } ;
struct TYPE_4__ {scalar_t__ get_fan_speed_rpm; } ;

/* Variables and functions */
 int AMD_IS_PX ; 
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int EINVAL ; 
 int amdgpu_dpm_get_fan_speed_rpm (struct amdgpu_device*,int*) ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_get_fan_speed_rpm (int /*<<< orphan*/ *,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_get_fan1_target(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	int err;
	u32 rpm = 0;

	/* Can't adjust fan when the card is off */
	if  ((adev->flags & AMD_IS_PX) &&
	     (adev->ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	if (is_support_sw_smu(adev)) {
		err = smu_get_fan_speed_rpm(&adev->smu, &rpm);
		if (err)
			return err;
	} else if (adev->powerplay.pp_funcs->get_fan_speed_rpm) {
		err = amdgpu_dpm_get_fan_speed_rpm(adev, &rpm);
		if (err)
			return err;
	}

	return sprintf(buf, "%i\n", rpm);
}