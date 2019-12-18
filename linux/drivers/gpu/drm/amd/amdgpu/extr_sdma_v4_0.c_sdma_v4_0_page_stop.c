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
struct TYPE_7__ {struct amdgpu_ring* buffer_funcs_ring; } ;
struct TYPE_6__ {int num_instances; TYPE_1__* instance; } ;
struct amdgpu_device {TYPE_3__ mman; TYPE_2__ sdma; } ;
struct TYPE_5__ {struct amdgpu_ring page; } ;

/* Variables and functions */
 int AMDGPU_MAX_SDMA_INSTANCES ; 
 int /*<<< orphan*/  IB_ENABLE ; 
 int /*<<< orphan*/  RB_ENABLE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32_SDMA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_PAGE_IB_CNTL ; 
 int /*<<< orphan*/  SDMA0_PAGE_RB_CNTL ; 
 int /*<<< orphan*/  WREG32_SDMA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_set_buffer_funcs_status (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_IB_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_PAGE_RB_CNTL ; 

__attribute__((used)) static void sdma_v4_0_page_stop(struct amdgpu_device *adev)
{
	struct amdgpu_ring *sdma[AMDGPU_MAX_SDMA_INSTANCES];
	u32 rb_cntl, ib_cntl;
	int i;
	bool unset = false;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		sdma[i] = &adev->sdma.instance[i].page;

		if ((adev->mman.buffer_funcs_ring == sdma[i]) &&
			(unset == false)) {
			amdgpu_ttm_set_buffer_funcs_status(adev, false);
			unset = true;
		}

		rb_cntl = RREG32_SDMA(i, mmSDMA0_PAGE_RB_CNTL);
		rb_cntl = REG_SET_FIELD(rb_cntl, SDMA0_PAGE_RB_CNTL,
					RB_ENABLE, 0);
		WREG32_SDMA(i, mmSDMA0_PAGE_RB_CNTL, rb_cntl);
		ib_cntl = RREG32_SDMA(i, mmSDMA0_PAGE_IB_CNTL);
		ib_cntl = REG_SET_FIELD(ib_cntl, SDMA0_PAGE_IB_CNTL,
					IB_ENABLE, 0);
		WREG32_SDMA(i, mmSDMA0_PAGE_IB_CNTL, ib_cntl);

		sdma[i]->sched.ready = false;
	}
}