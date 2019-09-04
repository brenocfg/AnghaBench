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
typedef  int /*<<< orphan*/  u32 ;
struct ci_power_info {scalar_t__ fan_is_controlled_by_smc; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_FAN_CTRL_AUTO ; 
 int /*<<< orphan*/  AMD_FAN_CTRL_MANUAL ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static u32 ci_dpm_get_fan_control_mode(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);

	if (pi->fan_is_controlled_by_smc)
		return AMD_FAN_CTRL_AUTO;
	else
		return AMD_FAN_CTRL_MANUAL;
}