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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static uint32_t ilk_wm_fbc(uint32_t pri_val, uint32_t horiz_pixels,
			   uint8_t cpp)
{
	/*
	 * Neither of these should be possible since this function shouldn't be
	 * called if the CRTC is off or the plane is invisible.  But let's be
	 * extra paranoid to avoid a potential divide-by-zero if we screw up
	 * elsewhere in the driver.
	 */
	if (WARN_ON(!cpp))
		return 0;
	if (WARN_ON(!horiz_pixels))
		return 0;

	return DIV_ROUND_UP(pri_val * 64, horiz_pixels * cpp) + 2;
}