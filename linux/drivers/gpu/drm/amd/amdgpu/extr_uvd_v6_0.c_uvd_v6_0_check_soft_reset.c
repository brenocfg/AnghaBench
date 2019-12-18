#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_2__ uvd; } ;
struct TYPE_3__ {int srbm_soft_reset; } ;

/* Variables and functions */
 int AMDGPU_UVD_STATUS_BUSY_MASK ; 
 scalar_t__ REG_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOFT_RESET_UVD ; 
 int /*<<< orphan*/  SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  SRBM_STATUS ; 
 int /*<<< orphan*/  UVD_BUSY ; 
 int /*<<< orphan*/  UVD_RQ_PENDING ; 
 int /*<<< orphan*/  mmSRBM_STATUS ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 

__attribute__((used)) static bool uvd_v6_0_check_soft_reset(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 tmp = RREG32(mmSRBM_STATUS);

	if (REG_GET_FIELD(tmp, SRBM_STATUS, UVD_RQ_PENDING) ||
	    REG_GET_FIELD(tmp, SRBM_STATUS, UVD_BUSY) ||
	    (RREG32(mmUVD_STATUS) & AMDGPU_UVD_STATUS_BUSY_MASK))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_UVD, 1);

	if (srbm_soft_reset) {
		adev->uvd.inst->srbm_soft_reset = srbm_soft_reset;
		return true;
	} else {
		adev->uvd.inst->srbm_soft_reset = 0;
		return false;
	}
}