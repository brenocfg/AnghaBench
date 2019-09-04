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
typedef  int u32 ;
struct TYPE_2__ {int htc_hyst_lmt; } ;
struct trinity_power_info {int thermal_auto_throttling; TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int HT (int) ; 
 int HT_MASK ; 
 int LT (int) ; 
 int LT_MASK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_SCLK_DPM_TTT ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void trinity_program_ttt(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 value = RREG32_SMC(SMU_SCLK_DPM_TTT);

	value &= ~(HT_MASK | LT_MASK);
	value |= HT((pi->thermal_auto_throttling + 49) * 8);
	value |= LT((pi->thermal_auto_throttling + 49 - pi->sys_info.htc_hyst_lmt) * 8);
	WREG32_SMC(SMU_SCLK_DPM_TTT, value);
}