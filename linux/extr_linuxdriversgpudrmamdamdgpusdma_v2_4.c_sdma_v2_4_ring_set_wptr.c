#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct amdgpu_ring {size_t me; int /*<<< orphan*/  wptr; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ mmSDMA0_GFX_RB_WPTR ; 
 scalar_t__* sdma_offsets ; 

__attribute__((used)) static void sdma_v2_4_ring_set_wptr(struct amdgpu_ring *ring)
{
	struct amdgpu_device *adev = ring->adev;

	WREG32(mmSDMA0_GFX_RB_WPTR + sdma_offsets[ring->me], lower_32_bits(ring->wptr) << 2);
}