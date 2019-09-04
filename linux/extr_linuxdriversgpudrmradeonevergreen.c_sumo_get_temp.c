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
 int /*<<< orphan*/  CG_THERMAL_STATUS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

int sumo_get_temp(struct radeon_device *rdev)
{
	u32 temp = RREG32(CG_THERMAL_STATUS) & 0xff;
	int actual_temp = temp - 49;

	return actual_temp * 1000;
}