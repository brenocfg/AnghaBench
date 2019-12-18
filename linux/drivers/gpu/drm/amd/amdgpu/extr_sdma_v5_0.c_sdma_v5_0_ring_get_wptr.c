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
typedef  int uint64_t ;
typedef  int u64 ;
typedef  int u32 ;
struct amdgpu_ring {size_t wptr_offs; int /*<<< orphan*/  me; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,...) ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR ; 
 int /*<<< orphan*/  mmSDMA0_GFX_RB_WPTR_HI ; 
 int /*<<< orphan*/  sdma_v5_0_get_reg_offset (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t sdma_v5_0_ring_get_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u64 *wptr = NULL;
	uint64_t local_wptr = 0;

	if (ring->use_doorbell) {
		/* XXX check if swapping is necessary on BE */
		wptr = ((u64 *)&adev->wb.wb[ring->wptr_offs]);
		DRM_DEBUG("wptr/doorbell before shift == 0x%016llx\n", *wptr);
		*wptr = (*wptr) >> 2;
		DRM_DEBUG("wptr/doorbell after shift == 0x%016llx\n", *wptr);
	} else {
		u32 lowbit, highbit;

		wptr = &local_wptr;
		lowbit = RREG32(sdma_v5_0_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR)) >> 2;
		highbit = RREG32(sdma_v5_0_get_reg_offset(adev, ring->me, mmSDMA0_GFX_RB_WPTR_HI)) >> 2;

		DRM_DEBUG("wptr [%i]high== 0x%08x low==0x%08x\n",
				ring->me, highbit, lowbit);
		*wptr = highbit;
		*wptr = (*wptr) << 32;
		*wptr |= lowbit;
	}

	return *wptr;
}