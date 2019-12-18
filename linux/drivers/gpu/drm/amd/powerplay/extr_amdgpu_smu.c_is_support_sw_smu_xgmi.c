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
 scalar_t__ CHIP_VEGA20 ; 
 int amdgpu_dpm ; 

bool is_support_sw_smu_xgmi(struct amdgpu_device *adev)
{
	if (amdgpu_dpm != 1)
		return false;

	if (adev->asic_type == CHIP_VEGA20)
		return true;

	return false;
}