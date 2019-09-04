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
struct radeon_device {scalar_t__ family; int flags; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV770 ; 
 int RADEON_IS_MOBILITY ; 
 int r600_dpm_get_vblank_time (struct radeon_device*) ; 

bool rv770_dpm_vblank_too_short(struct radeon_device *rdev)
{
	u32 vblank_time = r600_dpm_get_vblank_time(rdev);
	u32 switch_limit = 200; /* 300 */

	/* RV770 */
	/* mclk switching doesn't seem to work reliably on desktop RV770s */
	if ((rdev->family == CHIP_RV770) &&
	    !(rdev->flags & RADEON_IS_MOBILITY))
		switch_limit = 0xffffffff; /* disable mclk switching */

	if (vblank_time < switch_limit)
		return true;
	else
		return false;

}