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
typedef  int u8 ;
typedef  int u32 ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int ATOM_S2_CURRENT_BL_LEVEL_MASK ; 
 int ATOM_S2_CURRENT_BL_LEVEL_SHIFT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmBIOS_SCRATCH_2 ; 

void
amdgpu_atombios_encoder_set_backlight_level_to_reg(struct amdgpu_device *adev,
					    u8 backlight_level)
{
	u32 bios_2_scratch;

	bios_2_scratch = RREG32(mmBIOS_SCRATCH_2);

	bios_2_scratch &= ~ATOM_S2_CURRENT_BL_LEVEL_MASK;
	bios_2_scratch |= ((backlight_level << ATOM_S2_CURRENT_BL_LEVEL_SHIFT) &
			   ATOM_S2_CURRENT_BL_LEVEL_MASK);

	WREG32(mmBIOS_SCRATCH_2, bios_2_scratch);
}