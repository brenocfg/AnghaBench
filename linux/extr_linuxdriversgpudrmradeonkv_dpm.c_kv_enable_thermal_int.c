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

/* Variables and functions */
 int /*<<< orphan*/  CG_THERMAL_INT_CTRL ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int THERM_INTH_MASK ; 
 int THERM_INTL_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kv_enable_thermal_int(struct radeon_device *rdev, bool enable)
{
	u32 thermal_int;

	thermal_int = RREG32_SMC(CG_THERMAL_INT_CTRL);
	if (enable)
		thermal_int |= THERM_INTH_MASK | THERM_INTL_MASK;
	else
		thermal_int &= ~(THERM_INTH_MASK | THERM_INTL_MASK);
	WREG32_SMC(CG_THERMAL_INT_CTRL, thermal_int);

}