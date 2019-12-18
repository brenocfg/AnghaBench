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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_instances; scalar_t__ has_page_queue; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32_SDMA (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0_F32_CNTL ; 
 int /*<<< orphan*/  WREG32_SDMA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_F32_CNTL ; 
 int /*<<< orphan*/  sdma_v4_0_gfx_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v4_0_page_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v4_0_rlc_stop (struct amdgpu_device*) ; 

__attribute__((used)) static void sdma_v4_0_enable(struct amdgpu_device *adev, bool enable)
{
	u32 f32_cntl;
	int i;

	if (enable == false) {
		sdma_v4_0_gfx_stop(adev);
		sdma_v4_0_rlc_stop(adev);
		if (adev->sdma.has_page_queue)
			sdma_v4_0_page_stop(adev);
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntl = RREG32_SDMA(i, mmSDMA0_F32_CNTL);
		f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, enable ? 0 : 1);
		WREG32_SDMA(i, mmSDMA0_F32_CNTL, f32_cntl);
	}
}