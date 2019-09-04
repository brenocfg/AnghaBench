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
struct pp_hwmgr {int dummy; } ;
struct TYPE_4__ {scalar_t__ load_type; } ;
struct TYPE_3__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_2__ firmware; TYPE_1__ powerplay; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_SMU ; 
 int /*<<< orphan*/  amdgpu_ucode_init_bo (struct amdgpu_device*) ; 
 int hwmgr_hw_init (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pp_hw_init(void *handle)
{
	int ret = 0;
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_SMU)
		amdgpu_ucode_init_bo(adev);

	ret = hwmgr_hw_init(hwmgr);

	if (ret)
		pr_err("powerplay hw init failed\n");

	return ret;
}