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
struct TYPE_2__ {struct amdgpu_ring* ring; } ;
struct amdgpu_device {TYPE_1__ vce; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCE ; 
 int VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK ; 
 int VCE_STATUS__JOB_BUSY_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
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
 int /*<<< orphan*/  mmVCE_SOFT_RESET ; 
 int /*<<< orphan*/  mmVCE_STATUS ; 
 int /*<<< orphan*/  mmVCE_VCPU_CNTL ; 
 int upper_32_bits (int) ; 
 int vce_v4_0_firmware_loaded (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vce_v4_0_mc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int vce_v4_0_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	int r;

	ring = &adev->vce.ring[0];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE), ring->ring_size / 4);

	ring = &adev->vce.ring[1];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR2), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR2), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO2), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI2), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE2), ring->ring_size / 4);

	ring = &adev->vce.ring[2];

	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_RPTR3), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_WPTR3), lower_32_bits(ring->wptr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_LO3), ring->gpu_addr);
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_BASE_HI3), upper_32_bits(ring->gpu_addr));
	WREG32(SOC15_REG_OFFSET(VCE, 0, mmVCE_RB_SIZE3), ring->ring_size / 4);

	vce_v4_0_mc_resume(adev);
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), VCE_STATUS__JOB_BUSY_MASK,
			~VCE_STATUS__JOB_BUSY_MASK);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_VCPU_CNTL), 1, ~0x200001);

	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_SOFT_RESET), 0,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
	mdelay(100);

	r = vce_v4_0_firmware_loaded(adev);

	/* clear BUSY flag */
	WREG32_P(SOC15_REG_OFFSET(VCE, 0, mmVCE_STATUS), 0, ~VCE_STATUS__JOB_BUSY_MASK);

	if (r) {
		DRM_ERROR("VCE not responding, giving up!!!\n");
		return r;
	}

	return 0;
}