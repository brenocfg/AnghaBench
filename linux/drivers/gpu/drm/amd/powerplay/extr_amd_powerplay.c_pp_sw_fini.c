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
struct TYPE_4__ {int /*<<< orphan*/ * fw; } ;
struct TYPE_3__ {struct pp_hwmgr* pp_handle; } ;
struct amdgpu_device {TYPE_2__ pm; TYPE_1__ powerplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwmgr_sw_fini (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_sw_fini(void *handle)
{
	struct amdgpu_device *adev = handle;
	struct pp_hwmgr *hwmgr = adev->powerplay.pp_handle;

	hwmgr_sw_fini(hwmgr);

	release_firmware(adev->pm.fw);
	adev->pm.fw = NULL;

	return 0;
}