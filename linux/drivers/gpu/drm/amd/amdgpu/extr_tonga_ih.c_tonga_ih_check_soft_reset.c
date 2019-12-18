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
struct amdgpu_device {TYPE_1__ irq; } ;

/* Variables and functions */
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_IH ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int SRBM_STATUS__IH_BUSY_MASK ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 

__attribute__((used)) static bool tonga_ih_check_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 tmp = RREG32(mmSRBM_STATUS);

	if (tmp & SRBM_STATUS__IH_BUSY_MASK)
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET,
						SOFT_RESET_IH, 1);

	if (srbm_soft_reset) {
		adev->irq.srbm_soft_reset = srbm_soft_reset;
		return true;
	} else {
		adev->irq.srbm_soft_reset = 0;
		return false;
	}
}