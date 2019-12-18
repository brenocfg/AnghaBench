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
typedef  int uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_power_limit ) (int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  smu_get_power_limit (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_show_power_cap(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	uint32_t limit = 0;

	if (is_support_sw_smu(adev)) {
		smu_get_power_limit(&adev->smu, &limit, false);
		return snprintf(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	} else if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->get_power_limit) {
		adev->powerplay.pp_funcs->get_power_limit(adev->powerplay.pp_handle, &limit, false);
		return snprintf(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	} else {
		return snprintf(buf, PAGE_SIZE, "\n");
	}
}