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
typedef  int u32 ;
struct amdgpu_ring {size_t wptr_offs; size_t me; struct amdgpu_device* adev; scalar_t__ use_pollmem; scalar_t__ use_doorbell; } ;
struct TYPE_2__ {int* wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int RREG32 (scalar_t__) ; 
 scalar_t__ mmSDMA0_GFX_RB_WPTR ; 
 scalar_t__* sdma_offsets ; 

__attribute__((used)) static uint64_t sdma_v3_0_ring_get_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u32 wptr;

	if (ring->use_doorbell || ring->use_pollmem) {
		/* XXX check if swapping is necessary on BE */
		wptr = ring->adev->wb.wb[ring->wptr_offs] >> 2;
	} else {
		wptr = RREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[ring->me]) >> 2;
	}

	return wptr;
}