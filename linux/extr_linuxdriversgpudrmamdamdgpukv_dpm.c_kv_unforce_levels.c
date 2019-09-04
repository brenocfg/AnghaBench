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
struct amdgpu_device {scalar_t__ asic_type; } ;

/* Variables and functions */
 scalar_t__ CHIP_KABINI ; 
 scalar_t__ CHIP_MULLINS ; 
 int /*<<< orphan*/  PPSMC_MSG_NoForcedLevel ; 
 int amdgpu_kv_notify_message_to_smu (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int kv_set_enabled_levels (struct amdgpu_device*) ; 

__attribute__((used)) static int kv_unforce_levels(struct amdgpu_device *adev)
{
	if (adev->asic_type == CHIP_KABINI || adev->asic_type == CHIP_MULLINS)
		return amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_NoForcedLevel);
	else
		return kv_set_enabled_levels(adev);
}