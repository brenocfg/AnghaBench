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
struct amdgpu_ring {size_t wptr_offs; int /*<<< orphan*/  me; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int READ_ONCE (int) ; 
 int RREG32_SDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_RB_WPTR ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_RB_WPTR_HI ; 

__attribute__((used)) static uint64_t sdma_v4_0_page_ring_get_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;
	u64 wptr;

	if (ring->use_doorbell) {
		/* XXX check if swapping is necessary on BE */
		wptr = READ_ONCE(*((u64 *)&adev->wb.wb[ring->wptr_offs]));
	} else {
		wptr = RREG32_SDMA(ring->me, mmSDMA0_PAGE_RB_WPTR_HI);
		wptr = wptr << 32;
		wptr |= RREG32_SDMA(ring->me, mmSDMA0_PAGE_RB_WPTR);
	}

	return wptr >> 2;
}