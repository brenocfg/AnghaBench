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
typedef  int uint32_t ;
struct TYPE_2__ {int num_instances; } ;
struct amdgpu_device {int cg_flags; TYPE_1__ sdma; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_SDMA_MGCG ; 
 int RREG32 (scalar_t__) ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE5_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE6_MASK ; 
 int SDMA0_CLK_CTRL__SOFT_OVERRIDE7_MASK ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmSDMA0_CLK_CTRL ; 
 scalar_t__* sdma_offsets ; 

__attribute__((used)) static void sdma_v3_0_update_sdma_medium_grain_clock_gating(
		struct amdgpu_device *adev,
		bool enable)
{
	uint32_t temp, data;
	int i;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG)) {
		for (i = 0; i < adev->sdma.num_instances; i++) {
			temp = data = RREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i]);
			data &= ~(SDMA0_CLK_CTRL__SOFT_OVERRIDE7_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE6_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE5_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				  SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK);
			if (data != temp)
				WREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i], data);
		}
	} else {
		for (i = 0; i < adev->sdma.num_instances; i++) {
			temp = data = RREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i]);
			data |= SDMA0_CLK_CTRL__SOFT_OVERRIDE7_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE6_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE5_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE4_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE3_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE2_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE1_MASK |
				SDMA0_CLK_CTRL__SOFT_OVERRIDE0_MASK;

			if (data != temp)
				WREG32(mmSDMA0_CLK_CTRL + sdma_offsets[i], data);
		}
	}
}