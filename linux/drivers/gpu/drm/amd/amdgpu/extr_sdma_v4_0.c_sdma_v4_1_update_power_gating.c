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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {int pg_flags; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_SDMA ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0 ; 
 int /*<<< orphan*/  SDMA0_CNTL__CTXEMPTY_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSDMA0_CNTL ; 

__attribute__((used)) static void
sdma_v4_1_update_power_gating(struct amdgpu_device *adev, bool enable)
{
	uint32_t def, data;

	if (enable && (adev->pg_flags & AMD_PG_SUPPORT_SDMA)) {
		/* enable idle interrupt */
		def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL));
		data |= SDMA0_CNTL__CTXEMPTY_INT_ENABLE_MASK;

		if (data != def)
			WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL), data);
	} else {
		/* disable idle interrupt */
		def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL));
		data &= ~SDMA0_CNTL__CTXEMPTY_INT_ENABLE_MASK;
		if (data != def)
			WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL), data);
	}
}