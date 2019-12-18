#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int ready; } ;
struct amdgpu_ring {TYPE_4__ sched; } ;
struct TYPE_7__ {int num_instances; TYPE_1__* instance; } ;
struct TYPE_6__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct amdgpu_device {TYPE_3__ sdma; TYPE_2__ mman; } ;
struct TYPE_5__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_ENABLE ; 
 int /*<<< orphan*/  RB_ENABLE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  SDMA0_GFX_IB_CNTL ; 
 int /*<<< orphan*/  SDMA0_GFX_RB_CNTL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 scalar_t__ mmSDMA0_GFX_IB_CNTL ; 
 scalar_t__ mmSDMA0_GFX_RB_CNTL ; 
 scalar_t__* sdma_offsets ; 

__attribute__((used)) static void sdma_v3_0_gfx_stop(struct amdgpu_device *adev)
{
	struct amdgpu_ring *sdma0 = &adev->sdma.instance[0].ring;
	struct amdgpu_ring *sdma1 = &adev->sdma.instance[1].ring;
	u32 rb_cntl, ib_cntl;
	int i;

	if ((adev->mman.buffer_funcs_ring == sdma0) ||
	    (adev->mman.buffer_funcs_ring == sdma1))
		amdgpu_ttm_set_buffer_funcs_status(adev, false);

	for (i = 0; i < adev->sdma.num_instances; i++) {
		rb_cntl = RREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i]);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_GFX_RB_CNTL, RB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_RB_CNTL + sdma_offsets[i], rb_cntl);
		ib_cntl = RREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i]);
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_GFX_IB_CNTL, IB_ENABLE, 0);
		WREG32(mmSDMA0_GFX_IB_CNTL + sdma_offsets[i], ib_cntl);
	}
	sdma0->sched.ready = false;
	sdma1->sched.ready = false;
}