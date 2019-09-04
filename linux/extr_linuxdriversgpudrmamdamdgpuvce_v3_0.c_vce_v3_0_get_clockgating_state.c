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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct amdgpu_device {int flags; TYPE_1__ pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_CG_SUPPORT_VCE_MGCG ; 
 int AMD_IS_APU ; 
 int CURRENT_PG_STATUS__VCE_PG_STATUS_MASK ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  GRBM_GFX_INDEX ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE_INSTANCE ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCURRENT_PG_STATUS ; 
 int /*<<< orphan*/  ixCURRENT_PG_STATUS_APU ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vce_v3_0_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int data;

	mutex_lock(&adev->pm.mutex);

	if (adev->flags & AMD_IS_APU)
		data = RREG32_SMC(ixCURRENT_PG_STATUS_APU);
	else
		data = RREG32_SMC(ixCURRENT_PG_STATUS);

	if (data & CURRENT_PG_STATUS__VCE_PG_STATUS_MASK) {
		DRM_INFO("Cannot get clockgating state when VCE is powergated.\n");
		goto out;
	}

	WREG32_FIELD(GRBM_GFX_INDEX, VCE_INSTANCE, 0);

	/* AMD_CG_SUPPORT_VCE_MGCG */
	data = RREG32(mmVCE_CLOCK_GATING_A);
	if (data & (0x04 << 4))
		*flags |= AMD_CG_SUPPORT_VCE_MGCG;

out:
	mutex_unlock(&adev->pm.mutex);
}