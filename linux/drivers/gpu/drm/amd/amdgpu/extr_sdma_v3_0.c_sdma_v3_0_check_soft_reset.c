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
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_SOFT_RESET__SOFT_RESET_SDMA1_MASK ; 
 int SRBM_SOFT_RESET__SOFT_RESET_SDMA_MASK ; 
 int SRBM_STATUS2__SDMA1_BUSY_MASK ; 
 int SRBM_STATUS2__SDMA_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS2 ; 

__attribute__((used)) static bool sdma_v3_0_check_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 tmp = RREG32(mmSRBM_STATUS2);

	if ((tmp & SRBM_STATUS2__SDMA_BUSY_MASK) ||
	    (tmp & SRBM_STATUS2__SDMA1_BUSY_MASK)) {
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_SDMA_MASK;
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_SDMA1_MASK;
	}

	if (srbm_soft_reset) {
		adev->sdma.srbm_soft_reset = srbm_soft_reset;
		return true;
	} else {
		adev->sdma.srbm_soft_reset = 0;
		return false;
	}
}