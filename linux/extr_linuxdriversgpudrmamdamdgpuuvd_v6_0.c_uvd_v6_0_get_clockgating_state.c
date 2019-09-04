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
 int /*<<< orphan*/  AMD_CG_SUPPORT_UVD_MGCG ; 
 int AMD_IS_APU ; 
 int CURRENT_PG_STATUS__UVD_PG_STATUS_MASK ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK ; 
 int /*<<< orphan*/  ixCURRENT_PG_STATUS ; 
 int /*<<< orphan*/  ixCURRENT_PG_STATUS_APU ; 
 int /*<<< orphan*/  mmUVD_CGC_CTRL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uvd_v6_0_get_clockgating_state(void *handle, u32 *flags)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int data;

	mutex_lock(&adev->pm.mutex);

	if (adev->flags & AMD_IS_APU)
		data = RREG32_SMC(ixCURRENT_PG_STATUS_APU);
	else
		data = RREG32_SMC(ixCURRENT_PG_STATUS);

	if (data & CURRENT_PG_STATUS__UVD_PG_STATUS_MASK) {
		DRM_INFO("Cannot get clockgating state when UVD is powergated.\n");
		goto out;
	}

	/* AMD_CG_SUPPORT_UVD_MGCG */
	data = RREG32(mmUVD_CGC_CTRL);
	if (data & UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK)
		*flags |= AMD_CG_SUPPORT_UVD_MGCG;

out:
	mutex_unlock(&adev->pm.mutex);
}