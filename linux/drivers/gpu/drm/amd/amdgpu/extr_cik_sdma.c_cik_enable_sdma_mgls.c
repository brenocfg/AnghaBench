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
struct amdgpu_device {int cg_flags; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_SDMA_LS ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmSDMA0_POWER_CNTL ; 

__attribute__((used)) static void cik_enable_sdma_mgls(struct amdgpu_device *adev,
				 bool enable)
{
	u32 orig, data;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS)) {
		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data |= 0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data |= 0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	} else {
		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET);
		data &= ~0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA0_REGISTER_OFFSET, data);

		orig = data = RREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET);
		data &= ~0x100;
		if (orig != data)
			WREG32(mmSDMA0_POWER_CNTL + SDMA1_REGISTER_OFFSET, data);
	}
}