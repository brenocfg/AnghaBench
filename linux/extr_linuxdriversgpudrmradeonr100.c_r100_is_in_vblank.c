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

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CRTC2_STATUS ; 
 int RADEON_CRTC2_VBLANK_CUR ; 
 int /*<<< orphan*/  RADEON_CRTC_STATUS ; 
 int RADEON_CRTC_VBLANK_CUR ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r100_is_in_vblank(struct radeon_device *rdev, int crtc)
{
	if (crtc == 0) {
		if (RREG32(RADEON_CRTC_STATUS) & RADEON_CRTC_VBLANK_CUR)
			return true;
		else
			return false;
	} else {
		if (RREG32(RADEON_CRTC2_STATUS) & RADEON_CRTC2_VBLANK_CUR)
			return true;
		else
			return false;
	}
}