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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AVIVO_D1CRTC_STATUS_POSITION ; 
 scalar_t__ RREG32 (scalar_t__) ; 
 scalar_t__* crtc_offsets ; 

__attribute__((used)) static bool avivo_is_counter_moving(struct radeon_device *rdev, int crtc)
{
	u32 pos1, pos2;

	pos1 = RREG32(AVIVO_D1CRTC_STATUS_POSITION + crtc_offsets[crtc]);
	pos2 = RREG32(AVIVO_D1CRTC_STATUS_POSITION + crtc_offsets[crtc]);

	if (pos1 != pos2)
		return true;
	else
		return false;
}