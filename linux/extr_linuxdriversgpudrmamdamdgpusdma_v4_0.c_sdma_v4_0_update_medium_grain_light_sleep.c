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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int num_instances; } ;
struct amdgpu_device {int cg_flags; TYPE_1__ sdma; } ;

/* Variables and functions */
 int AMD_CG_SUPPORT_SDMA_LS ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0 ; 
 int /*<<< orphan*/  SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK ; 
 int /*<<< orphan*/  SDMA1 ; 
 int /*<<< orphan*/  SDMA1_POWER_CNTL__MEM_POWER_OVERRIDE_MASK ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_POWER_CNTL ; 
 int /*<<< orphan*/  mmSDMA1_POWER_CNTL ; 

__attribute__((used)) static void sdma_v4_0_update_medium_grain_light_sleep(
		struct amdgpu_device *adev,
		bool enable)
{
	uint32_t data, def;

	if (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_LS)) {
		/* 1-not override: enable sdma0 mem light sleep */
		def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL));
		data |= SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
		if (def != data)
			WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL), data);

		/* 1-not override: enable sdma1 mem light sleep */
		if (adev->sdma.num_instances > 1) {
			def = data = RREG32(SOC15_REG_OFFSET(SDMA1, 0, mmSDMA1_POWER_CNTL));
			data |= SDMA1_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
			if (def != data)
				WREG32(SOC15_REG_OFFSET(SDMA1, 0, mmSDMA1_POWER_CNTL), data);
		}
	} else {
		/* 0-override:disable sdma0 mem light sleep */
		def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL));
		data &= ~SDMA0_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
		if (def != data)
			WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL), data);

		/* 0-override:disable sdma1 mem light sleep */
		if (adev->sdma.num_instances > 1) {
			def = data = RREG32(SOC15_REG_OFFSET(SDMA1, 0, mmSDMA1_POWER_CNTL));
			data &= ~SDMA1_POWER_CNTL__MEM_POWER_OVERRIDE_MASK;
			if (def != data)
				WREG32(SOC15_REG_OFFSET(SDMA1, 0, mmSDMA1_POWER_CNTL), data);
		}
	}
}