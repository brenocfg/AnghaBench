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
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pp_handle; TYPE_1__* pp_funcs; } ;
struct amdgpu_device {TYPE_2__ powerplay; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* smu_i2c_bus_access ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 struct amdgpu_device* to_amdgpu_device (struct i2c_adapter*) ; 

__attribute__((used)) static bool smu_v11_0_i2c_bus_lock(struct i2c_adapter *control)
{
	struct amdgpu_device *adev = to_amdgpu_device(control);

	/* Send  PPSMC_MSG_RequestI2CBus */
	if (!adev->powerplay.pp_funcs->smu_i2c_bus_access)
		goto Fail;


	if (!adev->powerplay.pp_funcs->smu_i2c_bus_access(adev->powerplay.pp_handle, true))
		return true;

Fail:
	return false;
}