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
struct amdgpu_device {scalar_t__ bios_scratch_reg_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_S3_ASIC_GUI_ENGINE_HUNG ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 

void amdgpu_atombios_scratch_regs_engine_hung(struct amdgpu_device *adev,
					      bool hung)
{
	u32 tmp = RREG32(adev->bios_scratch_reg_offset + 3);

	if (hung)
		tmp |= ATOM_S3_ASIC_GUI_ENGINE_HUNG;
	else
		tmp &= ~ATOM_S3_ASIC_GUI_ENGINE_HUNG;

	WREG32(adev->bios_scratch_reg_offset + 3, tmp);
}