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
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_STATUS__MCB_BUSY_MASK ; 
 int SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK ; 
 int SRBM_STATUS__MCC_BUSY_MASK ; 
 int SRBM_STATUS__MCD_BUSY_MASK ; 
 int SRBM_STATUS__VMC_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gmc_v7_0_wait_for_idle(void *handle)
{
	unsigned i;
	u32 tmp;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	for (i = 0; i < adev->usec_timeout; i++) {
		/* read MC_STATUS */
		tmp = RREG32(mmSRBM_STATUS) & (SRBM_STATUS__MCB_BUSY_MASK |
					       SRBM_STATUS__MCB_NON_DISPLAY_BUSY_MASK |
					       SRBM_STATUS__MCC_BUSY_MASK |
					       SRBM_STATUS__MCD_BUSY_MASK |
					       SRBM_STATUS__VMC_BUSY_MASK);
		if (!tmp)
			return 0;
		udelay(1);
	}
	return -ETIMEDOUT;

}