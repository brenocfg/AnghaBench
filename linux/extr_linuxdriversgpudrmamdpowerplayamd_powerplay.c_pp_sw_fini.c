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
struct pp_hwmgr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fw; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct TYPE_4__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_3__ pm; TYPE_2__ firmware; TYPE_1__ powerplay; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_SMU ; 
 int /*<<< orphan*/  amdgpu_ucode_fini_bo (struct amdgpu_device*) ; 
 int /*<<< orphan*/  hwmgr_sw_fini (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_sw_fini(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	hwmgr_sw_fini(hwmgr);

	if (adev->firmware.load_type == AMDGPU_FW_LOAD_SMU) {
		release_firmware(adev->pm.fw);
		adev->pm.fw = NULL;
		amdgpu_ucode_fini_bo(adev);
	}

	return 0;
}