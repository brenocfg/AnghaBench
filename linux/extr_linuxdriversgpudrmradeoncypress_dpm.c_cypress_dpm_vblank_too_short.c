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
typedef  scalar_t__ u32 ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ r600_dpm_get_vblank_time (struct radeon_device*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

bool cypress_dpm_vblank_too_short(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 vblank_time = r600_dpm_get_vblank_time(rdev);
	/* we never hit the non-gddr5 limit so disable it */
	u32 switch_limit = pi->mem_gddr5 ? 450 : 0;

	if (vblank_time < switch_limit)
		return true;
	else
		return false;

}