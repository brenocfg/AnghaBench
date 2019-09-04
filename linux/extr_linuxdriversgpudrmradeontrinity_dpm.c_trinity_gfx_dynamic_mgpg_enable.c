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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS_PG_CNTL (int) ; 
 int /*<<< orphan*/  DS_PG_CNTL_MASK ; 
 int /*<<< orphan*/  DS_PG_EN (int) ; 
 int /*<<< orphan*/  DS_PG_EN_MASK ; 
 int /*<<< orphan*/  PM_I_CNTL_1 ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_S_PG_CNTL ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_gfx_dynamic_mgpg_config (struct radeon_device*) ; 

__attribute__((used)) static void trinity_gfx_dynamic_mgpg_enable(struct radeon_device *rdev,
					    bool enable)
{
	u32 value;

	if (enable) {
		value = RREG32_SMC(PM_I_CNTL_1);
		value &= ~DS_PG_CNTL_MASK;
		value |= DS_PG_CNTL(1);
		WREG32_SMC(PM_I_CNTL_1, value);

		value = RREG32_SMC(SMU_S_PG_CNTL);
		value &= ~DS_PG_EN_MASK;
		value |= DS_PG_EN(1);
		WREG32_SMC(SMU_S_PG_CNTL, value);
	} else {
		value = RREG32_SMC(SMU_S_PG_CNTL);
		value &= ~DS_PG_EN_MASK;
		WREG32_SMC(SMU_S_PG_CNTL, value);

		value = RREG32_SMC(PM_I_CNTL_1);
		value &= ~DS_PG_CNTL_MASK;
		WREG32_SMC(PM_I_CNTL_1, value);
	}

	trinity_gfx_dynamic_mgpg_config(rdev);

}