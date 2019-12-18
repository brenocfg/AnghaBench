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
 int SDMA0_STATUS_REG__IDLE_MASK ; 
 int /*<<< orphan*/  mmSDMA0_STATUS_REG ; 
 int /*<<< orphan*/  sdma_v5_0_get_reg_offset (struct amdgpu_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sdma_v5_0_wait_for_idle(void *handle)
{
	unsigned i;
	u32 sdma0, sdma1;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	for (i = 0; i < adev->usec_timeout; i++) {
		sdma0 = RREG32(sdma_v5_0_get_reg_offset(adev, 0, mmSDMA0_STATUS_REG));
		sdma1 = RREG32(sdma_v5_0_get_reg_offset(adev, 1, mmSDMA0_STATUS_REG));

		if (sdma0 & sdma1 & SDMA0_STATUS_REG__IDLE_MASK)
			return 0;
		udelay(1);
	}
	return -ETIMEDOUT;
}