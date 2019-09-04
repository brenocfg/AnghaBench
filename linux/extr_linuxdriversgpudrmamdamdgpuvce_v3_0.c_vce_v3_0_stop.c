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
struct TYPE_2__ {int harvest_config; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  grbm_idx_mutex; TYPE_1__ vce; } ;

/* Variables and functions */
 scalar_t__ CHIP_STONEY ; 
 int /*<<< orphan*/  CLK_EN ; 
 int /*<<< orphan*/  ECPU_SOFT_RESET ; 
 int /*<<< orphan*/  GET_VCE_INSTANCE (int) ; 
 int /*<<< orphan*/  VCE_SOFT_RESET ; 
 int /*<<< orphan*/  VCE_VCPU_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX_DEFAULT ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vce_v3_0_stop(struct amdgpu_device *adev)
{
	int idx;

	mutex_lock(&adev->grbm_idx_mutex);
	for (idx = 0; idx < 2; ++idx) {
		if (adev->vce.harvest_config & (1 << idx))
			continue;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		if (adev->asic_type >= CHIP_STONEY)
			WREG32_P(mmVCE_VCPU_CNTL, 0, ~0x200001);
		else
			WREG32_FIELD(VCE_VCPU_CNTL, CLK_EN, 0);

		/* hold on ECPU */
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 1);

		/* clear VCE STATUS */
		WREG32(mmVCE_STATUS, 0);
	}

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	return 0;
}