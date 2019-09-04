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
struct TYPE_2__ {int num_instances; } ;
struct amdgpu_device {TYPE_1__ sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALT ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  SDMA0_F32_CNTL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mmSDMA0_F32_CNTL ; 
 scalar_t__* sdma_offsets ; 
 int /*<<< orphan*/  sdma_v3_0_gfx_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sdma_v3_0_rlc_stop (struct amdgpu_device*) ; 

__attribute__((used)) static void sdma_v3_0_enable(struct amdgpu_device *adev, bool enable)
{
	u32 f32_cntl;
	int i;

	if (!enable) {
		sdma_v3_0_gfx_stop(adev);
		sdma_v3_0_rlc_stop(adev);
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		f32_cntl = RREG32(mmSDMA0_F32_CNTL + sdma_offsets[i]);
		if (enable)
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 0);
		else
			f32_cntl = REG_SET_FIELD(f32_cntl, SDMA0_F32_CNTL, HALT, 1);
		WREG32(mmSDMA0_F32_CNTL + sdma_offsets[i], f32_cntl);
	}
}