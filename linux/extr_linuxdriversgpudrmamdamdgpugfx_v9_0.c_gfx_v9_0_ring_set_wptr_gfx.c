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
struct amdgpu_ring {size_t wptr_offs; int /*<<< orphan*/  wptr; int /*<<< orphan*/  doorbell_index; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WDOORBELL64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR_HI ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v9_0_ring_set_wptr_gfx(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring->use_doorbell) {
		/* XXX check if swapping is necessary on BE */
		atomic64_set((atomic64_t*)&adev->wb.wb[ring->wptr_offs], ring->wptr);
		WDOORBELL64(ring->doorbell_index, ring->wptr);
	} else {
		WREG32_SOC15(GC, 0, mmCP_RB0_WPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(GC, 0, mmCP_RB0_WPTR_HI, upper_32_bits(ring->wptr));
	}
}