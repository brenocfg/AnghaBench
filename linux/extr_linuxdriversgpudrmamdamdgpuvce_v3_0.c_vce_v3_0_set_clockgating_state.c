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
typedef  int uint32_t ;
struct TYPE_2__ {int harvest_config; } ;
struct amdgpu_device {int cg_flags; int /*<<< orphan*/  grbm_idx_mutex; TYPE_1__ vce; } ;
typedef  enum amd_clockgating_state { ____Placeholder_amd_clockgating_state } amd_clockgating_state ;

/* Variables and functions */
 int AMD_CG_STATE_GATE ; 
 int AMD_CG_SUPPORT_VCE_MGCG ; 
 int GET_VCE_INSTANCE (int) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int mmGRBM_GFX_INDEX_DEFAULT ; 
 int /*<<< orphan*/  mmVCE_CLOCK_GATING_A ; 
 int /*<<< orphan*/  mmVCE_UENC_CLOCK_GATING ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vce_v3_0_set_vce_sw_clock_gating (struct amdgpu_device*,int) ; 

__attribute__((used)) static int vce_v3_0_set_clockgating_state(void *handle,
					  enum amd_clockgating_state state)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE) ? true : false;
	int i;

	if (!(adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG))
		return 0;

	mutex_lock(&adev->grbm_idx_mutex);
	for (i = 0; i < 2; i++) {
		/* Program VCE Instance 0 or 1 if not harvested */
		if (adev->vce.harvest_config & (1 << i))
			continue;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(i));

		if (!enable) {
			/* initialize VCE_CLOCK_GATING_A: Clock ON/OFF delay */
			uint32_t data = RREG32(mmVCE_CLOCK_GATING_A);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(mmVCE_CLOCK_GATING_A, data);

			/* initialize VCE_UENC_CLOCK_GATING: Clock ON/OFF delay */
			data = RREG32(mmVCE_UENC_CLOCK_GATING);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(mmVCE_UENC_CLOCK_GATING, data);
		}

		vce_v3_0_set_vce_sw_clock_gating(adev, enable);
	}

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	return 0;
}