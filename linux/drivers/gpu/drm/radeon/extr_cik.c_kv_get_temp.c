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
 int RREG32_SMC (int) ; 

int kv_get_temp(struct radeon_device *rdev)
{
	u32 temp;
	int actual_temp = 0;

	temp = RREG32_SMC(0xC0300E0C);

	if (temp)
		actual_temp = (temp / 8) - 49;
	else
		actual_temp = 0;

	actual_temp = actual_temp * 1000;

	return actual_temp;
}