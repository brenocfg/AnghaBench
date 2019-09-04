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
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_ring {size_t wptr_offs; struct amdgpu_device* adev; scalar_t__ use_doorbell; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCP_RB0_WPTR ; 

__attribute__((used)) static u64 gfx_v8_0_ring_get_wptr_gfx(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring->use_doorbell)
		/* XXX check if swapping is necessary on BE */
		return ring->adev->wb.wb[ring->wptr_offs];
	else
		return RREG32(mmCP_RB0_WPTR);
}