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
typedef  scalar_t__ uint32_t ;
struct amdgpu_ring {int dummy; } ;
struct TYPE_8__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_7__ {int num_instances; TYPE_2__* instance; scalar_t__ has_page_queue; } ;
struct TYPE_5__ {scalar_t__ load_type; } ;
struct amdgpu_device {TYPE_4__ mman; TYPE_3__ sdma; TYPE_1__ firmware; } ;
struct TYPE_6__ {struct amdgpu_ring page; struct amdgpu_ring ring; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int /*<<< orphan*/  HALT ; 
 scalar_t__ REG_SET_FIELD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ RREG32_SDMA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_CNTL ; 
 int /*<<< orphan*/  SDMA0_F32_CNTL ; 
 int /*<<< orphan*/  UTC_L1_ENABLE ; 
 int /*<<< orphan*/  WREG32_SDMA (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int amdgpu_ring_test_helper (struct amdgpu_ring*) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmSDMA0_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_F32_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL ; 
 int /*<<< orphan*/  sdma_v4_0_ctx_switch_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v4_0_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  sdma_v4_0_gfx_resume (struct amdgpu_device*,int) ; 
 int sdma_v4_0_load_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v4_0_page_resume (struct amdgpu_device*,int) ; 
 int sdma_v4_0_rlc_resume (struct amdgpu_device*) ; 

__attribute__((used)) static int sdma_v4_0_start(struct amdgpu_device *adev)
{
	struct amdgpu_ring *ring;
	int i, r = 0;

	if (amdgpu_sriov_vf(adev)) {
		sdma_v4_0_ctx_switch_enable(adev, false);
		sdma_v4_0_enable(adev, false);
	} else {

		if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
			r = sdma_v4_0_load_microcode(adev);
			if (r)
				return r;
		}

		/* unhalt the MEs */
		sdma_v4_0_enable(adev, true);
		/* enable sdma ring preemption */
		sdma_v4_0_ctx_switch_enable(adev, true);
	}

	/* start the gfx rings and rlc compute queues */
	for (i = 0; i < adev->sdma.num_instances; i++) {
		uint32_t temp;

		WREG32_SDMA(i, mmSDMA0_SEM_WAIT_FAIL_TIMER_CNTL, 0);
		sdma_v4_0_gfx_resume(adev, i);
		if (adev->sdma.has_page_queue)
			sdma_v4_0_page_resume(adev, i);

		/* set utc l1 enable flag always to 1 */
		temp = RREG32_SDMA(i, mmSDMA0_CNTL);
		temp = REG_SET_FIELD(temp, SDMA0_CNTL, UTC_L1_ENABLE, 1);
		WREG32_SDMA(i, mmSDMA0_CNTL, temp);

		if (!amdgpu_sriov_vf(adev)) {
			/* unhalt engine */
			temp = RREG32_SDMA(i, mmSDMA0_F32_CNTL);
			temp = REG_SET_FIELD(temp, SDMA0_F32_CNTL, HALT, 0);
			WREG32_SDMA(i, mmSDMA0_F32_CNTL, temp);
		}
	}

	if (amdgpu_sriov_vf(adev)) {
		sdma_v4_0_ctx_switch_enable(adev, true);
		sdma_v4_0_enable(adev, true);
	} else {
		r = sdma_v4_0_rlc_resume(adev);
		if (r)
			return r;
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;

		r = amdgpu_ring_test_helper(ring);
		if (r)
			return r;

		if (adev->sdma.has_page_queue) {
			struct amdgpu_ring *page = &adev->sdma.instance[i].page;

			r = amdgpu_ring_test_helper(page);
			if (r)
				return r;

			if (adev->mman.buffer_funcs_ring == page)
				amdgpu_ttm_set_buffer_funcs_status(adev, true);
		}

		if (adev->mman.buffer_funcs_ring == ring)
			amdgpu_ttm_set_buffer_funcs_status(adev, true);
	}

	return r;
}