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
struct amdgpu_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IH_BUSY ; 
 int /*<<< orphan*/  REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRBM_STATUS ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iceland_ih_wait_for_idle(void *handle)
{
	unsigned i;
	u32 tmp;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	for (i = 0; i < adev->usec_timeout; i++) {
		/* read MC_STATUS */
		tmp = RREG32(mmSRBM_STATUS);
		if (!REG_GET_FIELD(tmp, SRBM_STATUS, IH_BUSY))
			return 0;
		udelay(1);
	}
	return -ETIMEDOUT;
}