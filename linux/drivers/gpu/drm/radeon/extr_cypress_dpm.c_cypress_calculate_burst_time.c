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
struct rv7xx_power_info {scalar_t__ mem_gddr5; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

u32 cypress_calculate_burst_time(struct radeon_device *rdev,
				 u32 engine_clock, u32 memory_clock)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 multiplier = pi->mem_gddr5 ? 1 : 2;
	u32 result = (4 * multiplier * engine_clock) / (memory_clock / 2);
	u32 burst_time;

	if (result <= 4)
		burst_time = 0;
	else if (result < 8)
		burst_time = result - 4;
	else {
		burst_time = result / 2 ;
		if (burst_time > 18)
			burst_time = 18;
	}

	return burst_time;
}