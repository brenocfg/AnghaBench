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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; int /*<<< orphan*/  smu; } ;
typedef  enum amd_pp_sensors { ____Placeholder_amd_pp_sensors } amd_pp_sensors ;
struct TYPE_3__ {int (* read_sensor ) (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ is_support_sw_smu (struct amdgpu_device*) ; 
 int smu_read_sensor (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 

int amdgpu_dpm_read_sensor(struct amdgpu_device *adev, enum amd_pp_sensors sensor,
			   void *data, uint32_t *size)
{
	int ret = 0;

	if (!data || !size)
		return -EINVAL;

	if (is_support_sw_smu(adev))
		ret = smu_read_sensor(&adev->smu, sensor, data, size);
	else {
		if (adev->powerplay.pp_funcs && adev->powerplay.pp_funcs->read_sensor)
			ret = adev->powerplay.pp_funcs->read_sensor((adev)->powerplay.pp_handle,
								    sensor, data, size);
		else
			ret = -EINVAL;
	}

	return ret;
}