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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {scalar_t__ bios_scratch_reg_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_S2_DEVICE_DPMS_STATE ; 
 int /*<<< orphan*/  ATOM_S2_VRI_BRIGHT_ENABLE ; 
 int /*<<< orphan*/  ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmBIOS_SCRATCH_0 ; 

__attribute__((used)) static void amdgpu_atombios_scratch_regs_init(struct amdgpu_device *adev)
{
	uint32_t bios_2_scratch, bios_6_scratch;

	adev->bios_scratch_reg_offset = mmBIOS_SCRATCH_0;

	bios_2_scratch = RREG32(adev->bios_scratch_reg_offset + 2);
	bios_6_scratch = RREG32(adev->bios_scratch_reg_offset + 6);

	/* let the bios control the backlight */
	bios_2_scratch &= ~ATOM_S2_VRI_BRIGHT_ENABLE;

	/* tell the bios not to handle mode switching */
	bios_6_scratch |= ATOM_S6_ACC_BLOCK_DISPLAY_SWITCH;

	/* clear the vbios dpms state */
	bios_2_scratch &= ~ATOM_S2_DEVICE_DPMS_STATE;

	WREG32(adev->bios_scratch_reg_offset + 2, bios_2_scratch);
	WREG32(adev->bios_scratch_reg_offset + 6, bios_6_scratch);
}