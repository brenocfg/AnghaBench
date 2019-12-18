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
struct amdgpu_ring {size_t wptr_offs; int /*<<< orphan*/  wptr; int /*<<< orphan*/  doorbell_index; scalar_t__ use_doorbell; struct amdgpu_device* adev; } ;
struct TYPE_6__ {void** wb; } ;
struct TYPE_5__ {TYPE_1__* inst; } ;
struct amdgpu_device {TYPE_3__ wb; TYPE_2__ vcn; } ;
struct TYPE_4__ {struct amdgpu_ring* ring_enc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  WDOORBELL32 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR ; 
 int /*<<< orphan*/  mmUVD_RB_WPTR2 ; 

__attribute__((used)) static void vcn_v2_0_enc_ring_set_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	if (ring == &adev->vcn.inst->ring_enc[0]) {
		if (ring->use_doorbell) {
			adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
			WDOORBELL32(ring->doorbell_index, lower_32_bits(ring->wptr));
		} else {
			WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		}
	} else {
		if (ring->use_doorbell) {
			adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
			WDOORBELL32(ring->doorbell_index, lower_32_bits(ring->wptr));
		} else {
			WREG32_SOC15(UVD, 0, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		}
	}
}