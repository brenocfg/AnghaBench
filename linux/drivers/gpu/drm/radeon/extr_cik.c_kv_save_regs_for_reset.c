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
struct radeon_device {int dummy; } ;
struct kv_reset_save_regs {int gmcon_reng_execute; int gmcon_misc; void* gmcon_misc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMCON_MISC ; 
 int /*<<< orphan*/  GMCON_MISC3 ; 
 int /*<<< orphan*/  GMCON_RENG_EXECUTE ; 
 int RENG_EXECUTE_ON_PWR_UP ; 
 int RENG_EXECUTE_ON_REG_UPDATE ; 
 void* RREG32 (int /*<<< orphan*/ ) ; 
 int STCTRL_STUTTER_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kv_save_regs_for_reset(struct radeon_device *rdev,
				   struct kv_reset_save_regs *save)
{
	save->gmcon_reng_execute = RREG32(GMCON_RENG_EXECUTE);
	save->gmcon_misc = RREG32(GMCON_MISC);
	save->gmcon_misc3 = RREG32(GMCON_MISC3);

	WREG32(GMCON_RENG_EXECUTE, save->gmcon_reng_execute & ~RENG_EXECUTE_ON_PWR_UP);
	WREG32(GMCON_MISC, save->gmcon_misc & ~(RENG_EXECUTE_ON_REG_UPDATE |
						STCTRL_STUTTER_EN));
}