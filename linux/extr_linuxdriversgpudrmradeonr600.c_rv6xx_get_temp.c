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
 int ASIC_T_MASK ; 
 int ASIC_T_SHIFT ; 
 int /*<<< orphan*/  CG_THERMAL_STATUS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

int rv6xx_get_temp(struct radeon_device *rdev)
{
	u32 temp = (RREG32(CG_THERMAL_STATUS) & ASIC_T_MASK) >>
		ASIC_T_SHIFT;
	int actual_temp = temp & 0xff;

	if (temp & 0x100)
		actual_temp -= 256;

	return actual_temp * 1000;
}