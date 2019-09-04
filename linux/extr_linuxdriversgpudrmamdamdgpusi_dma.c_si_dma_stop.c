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
typedef  int /*<<< orphan*/  u32 ;
struct amdgpu_ring {int ready; } ;
struct TYPE_4__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_5__ {unsigned int num_instances; TYPE_3__* instance; } ;
struct amdgpu_device {TYPE_1__ mman; TYPE_2__ sdma; } ;
struct TYPE_6__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 scalar_t__ DMA_RB_CNTL ; 
 int /*<<< orphan*/  DMA_RB_ENABLE ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 scalar_t__* sdma_offsets ; 

__attribute__((used)) static void si_dma_stop(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	u32 rb_cntl;
	unsigned i;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		/* dma0 */
		rb_cntl = RREG32(DMA_RB_CNTL + sdma_offsets[i]);
		rb_cntl &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl);

		if (adev->mman.buffer_funcs_ring == ring)
			amdgpu_ttm_set_buffer_funcs_status(adev, false);
		ring->ready = false;
	}
}