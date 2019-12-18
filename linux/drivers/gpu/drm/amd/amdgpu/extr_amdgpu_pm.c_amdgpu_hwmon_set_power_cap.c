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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int (* set_power_limit ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int kstrtou32 (char const*,int,int*) ; 
 int smu_set_power_limit (int /*<<< orphan*/ *,int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_set_power_cap(struct device *dev,
		struct device_attribute *attr,
		const char *buf,
		size_t count)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	int err;
	u32 value;

	err = kstrtou32(buf, 10, &value);
	if (err)
		return err;

	value = value / 1000000; /* convert to Watt */

	if (is_support_sw_smu(adev)) {
		err = smu_set_power_limit(&adev->smu, value);
	} else if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->set_power_limit) {
		err = adev->powerplay.pp_funcs->set_power_limit(adev->powerplay.pp_handle, value);
	} else {
		err = -EINVAL;
	}

	if (err)
		return err;

	return count;
}