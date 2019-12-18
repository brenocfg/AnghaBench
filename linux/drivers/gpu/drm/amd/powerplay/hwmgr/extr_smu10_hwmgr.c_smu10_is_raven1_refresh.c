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
struct pp_hwmgr {int smu_version; struct amdgpu_device* adev; } ;
struct amdgpu_device {scalar_t__ asic_type; int rev_id; } ;

/* Variables and functions */
 scalar_t__ CHIP_RAVEN ; 

__attribute__((used)) static bool smu10_is_raven1_refresh(struct pp_hwmgr *hwmgr)
{
	struct amdgpu_device *adev = hwmgr->adev;
	if ((adev->asic_type == CHIP_RAVEN) &&
	    (adev->rev_id != 0x15d8) &&
	    (hwmgr->smu_version >= 0x41e2b))
		return true;
	else
		return false;
}