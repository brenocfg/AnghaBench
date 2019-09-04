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
typedef  int uint32_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDMA0 ; 
 int SDMA0_CNTL__CTXEMPTY_INT_ENABLE_MASK ; 
 int SDMA0_POWER_CNTL__ON_OFF_CONDITION_HOLD_TIME_MASK ; 
 int SDMA0_POWER_CNTL__ON_OFF_STATUS_DURATION_TIME_MASK ; 
 int SDMA0_POWER_CNTL__PG_CNTL_ENABLE_MASK ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmSDMA0_CNTL ; 
 int /*<<< orphan*/  mmSDMA0_POWER_CNTL ; 
 int mmSDMA0_POWER_CNTL_DEFAULT ; 

__attribute__((used)) static void sdma_v4_1_init_power_gating(struct amdgpu_device *adev)
{
	uint32_t def, data;

	/* Enable HW based PG. */
	def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL));
	data |= SDMA0_POWER_CNTL__PG_CNTL_ENABLE_MASK;
	if (data != def)
		WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL), data);

	/* enable interrupt */
	def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL));
	data |= SDMA0_CNTL__CTXEMPTY_INT_ENABLE_MASK;
	if (data != def)
		WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_CNTL), data);

	/* Configure hold time to filter in-valid power on/off request. Use default right now */
	def = data = RREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL));
	data &= ~SDMA0_POWER_CNTL__ON_OFF_CONDITION_HOLD_TIME_MASK;
	data |= (mmSDMA0_POWER_CNTL_DEFAULT & SDMA0_POWER_CNTL__ON_OFF_CONDITION_HOLD_TIME_MASK);
	/* Configure switch time for hysteresis purpose. Use default right now */
	data &= ~SDMA0_POWER_CNTL__ON_OFF_STATUS_DURATION_TIME_MASK;
	data |= (mmSDMA0_POWER_CNTL_DEFAULT & SDMA0_POWER_CNTL__ON_OFF_STATUS_DURATION_TIME_MASK);
	if(data != def)
		WREG32(SOC15_REG_OFFSET(SDMA0, 0, mmSDMA0_POWER_CNTL), data);
}