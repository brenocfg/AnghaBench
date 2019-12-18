#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct amdgpu_ring {size_t me; size_t wptr_offs; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * wb; } ;
struct TYPE_6__ {TYPE_2__* inst; } ;
struct amdgpu_device {TYPE_1__ wb; TYPE_3__ vcn; } ;
struct TYPE_5__ {struct amdgpu_ring* ring_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32_SOC15 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR2 ; 

__attribute__((used)) static uint64_t vcn_v2_5_enc_ring_get_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring == &adev->vcn.inst[ring->me].ring_enc[0]) {
		if (ring->use_doorbell)
			return adev->wb.wb[ring->wptr_offs];
		else
			return RREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR);
	} else {
		if (ring->use_doorbell)
			return adev->wb.wb[ring->wptr_offs];
		else
			return RREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR2);
	}
}