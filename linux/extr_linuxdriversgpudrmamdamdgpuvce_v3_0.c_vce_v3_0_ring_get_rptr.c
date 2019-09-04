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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_ring {int me; struct amdgpu_device* adev; } ;
struct TYPE_2__ {scalar_t__ harvest_config; } ;
struct amdgpu_device {int /*<<< orphan*/  grbm_idx_mutex; TYPE_1__ vce; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_VCE_HARVEST_VCE0 ; 
 scalar_t__ AMDGPU_VCE_HARVEST_VCE1 ; 
 int /*<<< orphan*/  GET_VCE_INSTANCE (int) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX ; 
 int /*<<< orphan*/  mmGRBM_GFX_INDEX_DEFAULT ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR2 ; 
 int /*<<< orphan*/  mmVCE_RB_RPTR3 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t vce_v3_0_ring_get_rptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u32 v;

	mutex_lock(&adev->grbm_idx_mutex);
	if (adev->vce.harvest_config == 0 ||
		adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE1)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	else if (adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	if (ring->me == 0)
		v = RREG32(mmVCE_RB_RPTR);
	else if (ring->me == 1)
		v = RREG32(mmVCE_RB_RPTR2);
	else
		v = RREG32(mmVCE_RB_RPTR3);

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	return v;
}