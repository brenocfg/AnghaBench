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
struct amdgpu_ring {int gpu_addr; int ring_size; int /*<<< orphan*/  wptr; } ;
struct TYPE_2__ {int harvest_config; struct amdgpu_ring* ring; } ;
struct amdgpu_device {scalar_t__ asic_type; int /*<<< orphan*/  grbm_idx_mutex; TYPE_1__ vce; } ;

/* Variables and functions */
 int AMDGPU_VCE_HARVEST_VCE0 ; 
 scalar_t__ CHIP_STONEY ; 
 int /*<<< orphan*/  CLK_EN ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ECPU_SOFT_RESET ; 
 int GET_VCE_INSTANCE (int) ; 
 int /*<<< orphan*/  JOB_BUSY ; 
 int /*<<< orphan*/  VCE_SOFT_RESET ; 
 int /*<<< orphan*/  VCE_STATUS ; 
 int /*<<< orphan*/  VCE_VCPU_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int mmGRBM_GFX_INDEX_DEFAULT ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_HI ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_HI2 ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_HI3 ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_LO ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_LO2 ; 
 int /*<<< orphan*/  mmVCE_RB_BASE_LO3 ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR2 ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR3 ; 
 int /*<<< orphan*/  mmVCE_RB_SIZE ; 
 int /*<<< orphan*/  mmVCE_RB_SIZE2 ; 
 int /*<<< orphan*/  mmVCE_RB_SIZE3 ; 
 int /*<<< orphan*/  mmVCE_RB_WPTR ; 
 int /*<<< orphan*/  mmVCE_RB_WPTR2 ; 
 int /*<<< orphan*/  mmVCE_RB_WPTR3 ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int upper_32_bits (int) ; 
 int vce_v3_0_firmware_loaded (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v3_0_mc_resume (struct amdgpu_device*,int) ; 

__attribute__((used)) static int vce_v3_0_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	int idx, r;

	mutex_lock(&adev->grbm_idx_mutex);
	for (idx = 0; idx < 2; ++idx) {
		if (adev->vce.harvest_config & (1 << idx))
			continue;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		/* Program instance 0 reg space for two instances or instance 0 case
		program instance 1 reg space for only instance 1 available case */
		if (idx != 1 || adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0) {
			ring = &adev->vce.ring[0];
			WREG32(mmVCE_RB_RPTR, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_WPTR, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_BASE_LO, ring->gpu_addr);
			WREG32(mmVCE_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
			WREG32(mmVCE_RB_SIZE, ring->ring_size / 4);

			ring = &adev->vce.ring[1];
			WREG32(mmVCE_RB_RPTR2, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_WPTR2, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_BASE_LO2, ring->gpu_addr);
			WREG32(mmVCE_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
			WREG32(mmVCE_RB_SIZE2, ring->ring_size / 4);

			ring = &adev->vce.ring[2];
			WREG32(mmVCE_RB_RPTR3, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_WPTR3, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_BASE_LO3, ring->gpu_addr);
			WREG32(mmVCE_RB_BASE_HI3, upper_32_bits(ring->gpu_addr));
			WREG32(mmVCE_RB_SIZE3, ring->ring_size / 4);
		}

		vce_v3_0_mc_resume(adev, idx);
		WREG32_FIELD(VCE_STATUS, JOB_BUSY, 1);

		if (adev->asic_type >= CHIP_STONEY)
			WREG32_P(mmVCE_VCPU_CNTL, 1, ~0x200001);
		else
			WREG32_FIELD(VCE_VCPU_CNTL, CLK_EN, 1);

		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 0);
		mdelay(100);

		r = vce_v3_0_firmware_loaded(adev);

		/* clear BUSY flag */
		WREG32_FIELD(VCE_STATUS, JOB_BUSY, 0);

		if (r) {
			DRM_ERROR("VCE not responding, giving up!!!\n");
			mutex_unlock(&adev->grbm_idx_mutex);
			return r;
		}
	}

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	return 0;
}