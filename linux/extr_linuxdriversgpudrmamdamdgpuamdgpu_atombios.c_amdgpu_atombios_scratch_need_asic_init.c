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
typedef  int u32 ;
struct amdgpu_device {scalar_t__ bios_scratch_reg_offset; } ;

/* Variables and functions */
 int ATOM_S7_ASIC_INIT_COMPLETE_MASK ; 
 int RREG32 (scalar_t__) ; 

bool amdgpu_atombios_scratch_need_asic_init(struct amdgpu_device *adev)
{
	u32 tmp = RREG32(adev->bios_scratch_reg_offset + 7);

	if (tmp & ATOM_S7_ASIC_INIT_COMPLETE_MASK)
		return false;
	else
		return true;
}