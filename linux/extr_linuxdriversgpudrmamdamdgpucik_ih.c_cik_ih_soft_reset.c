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
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SRBM_SOFT_RESET__SOFT_RESET_IH_MASK ; 
 int SRBM_STATUS__IH_BUSY_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mmSRBM_SOFT_RESET ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cik_ih_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	u32 srbm_soft_reset = 0;
	u32 tmp = RREG32(mmSRBM_STATUS);

	if (tmp & SRBM_STATUS__IH_BUSY_MASK)
		srbm_soft_reset |= SRBM_SOFT_RESET__SOFT_RESET_IH_MASK;

	if (srbm_soft_reset) {
		tmp = RREG32(mmSRBM_SOFT_RESET);
		tmp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", tmp);
		WREG32(mmSRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		tmp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, tmp);
		tmp = RREG32(mmSRBM_SOFT_RESET);

		/* Wait a little for things to settle down */
		udelay(50);
	}

	return 0;
}