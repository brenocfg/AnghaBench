#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int srbm_soft_reset; } ;
struct amdgpu_device {int flags; TYPE_1__ gmc; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_MC ; 
 int /*<<< orphan*/  SOFT_RESET_VMC ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int SRBM_STATUS__MCB_BUSY_MASK ; 
 int SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK ; 
 int SRBM_STATUS__MCC_BUSY_MASK ; 
 int SRBM_STATUS__MCD_BUSY_MASK ; 
 int SRBM_STATUS__VMC_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 

__attribute__((used)) static bool gmc_v8_0_check_soft_reset(void *handle)
{
	u32 srbm_soft_reset = 0;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 tmp = RREG32(mmSRBM_STATUS);

	if (tmp & SRBM_STATUS__VMC_BUSY_MASK)
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
						SRBM_SOFT_RESET, SOFT_RESET_VMC, 1);

	if (tmp & (SRBM_STATUS__MCB_BUSY_MASK | SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
		   SRBM_STATUS__MCC_BUSY_MASK | SRBM_STATUS__MCD_BUSY_MASK)) {
		if (!(adev->flags & AMD_IS_APU))
			srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
							SRBM_SOFT_RESET, SOFT_RESET_MC, 1);
	}
	if (srbm_soft_reset) {
		adev->gmc.srbm_soft_reset = srbm_soft_reset;
		return true;
	} else {
		adev->gmc.srbm_soft_reset = 0;
		return false;
	}
}