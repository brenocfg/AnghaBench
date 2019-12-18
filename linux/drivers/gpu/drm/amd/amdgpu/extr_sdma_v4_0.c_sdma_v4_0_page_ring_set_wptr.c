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
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_ring {size_t wptr_offs; int wptr; int /*<<< orphan*/  me; int /*<<< orphan*/  doorbell_index; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOORBELL64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_RB_WPTR ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_RB_WPTR_HI ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void sdma_v4_0_page_ring_set_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring->use_doorbell) {
		u64 *wb = (u64 *)&adev->wb.wb[ring->wptr_offs];

		/* XXX check if swapping is necessary on BE */
		WRITE_ONCE(*wb, (ring->wptr << 2));
		WDOORBELL64(ring->doorbell_index, ring->wptr << 2);
	} else {
		uint64_t wptr = ring->wptr << 2;

		WREG32_SDMA(ring->me, mmSDMA0_PAGE_RB_WPTR,
			    lower_32_bits(wptr));
		WREG32_SDMA(ring->me, mmSDMA0_PAGE_RB_WPTR_HI,
			    upper_32_bits(wptr));
	}
}