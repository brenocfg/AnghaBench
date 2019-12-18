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
typedef  int u32 ;
struct radeon_device {int dummy; } ;
struct ci_power_info {int fan_ctrl_is_in_default_mode; int /*<<< orphan*/  t_min; int /*<<< orphan*/  fan_ctrl_default_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int FDO_PWM_MODE (int /*<<< orphan*/ ) ; 
 int FDO_PWM_MODE_MASK ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int TMIN (int /*<<< orphan*/ ) ; 
 int TMIN_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_fan_ctrl_set_default_mode(struct radeon_device *rdev)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;

	if (!pi->fan_ctrl_is_in_default_mode) {
		tmp = RREG32_SMC(CG_FDO_CTRL2) & ~FDO_PWM_MODE_MASK;
		tmp |= FDO_PWM_MODE(pi->fan_ctrl_default_mode);
		WREG32_SMC(CG_FDO_CTRL2, tmp);

		tmp = RREG32_SMC(CG_FDO_CTRL2) & ~TMIN_MASK;
		tmp |= TMIN(pi->t_min);
		WREG32_SMC(CG_FDO_CTRL2, tmp);
		pi->fan_ctrl_is_in_default_mode = true;
	}
}