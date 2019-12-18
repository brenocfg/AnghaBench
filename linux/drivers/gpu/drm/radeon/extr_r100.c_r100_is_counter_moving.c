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
 int /*<<< orphan*/  RADEON_CRTC2_VLINE_CRNT_VLINE ; 
 int /*<<< orphan*/  RADEON_CRTC_VLINE_CRNT_VLINE ; 
 int RADEON_CRTC_V_TOTAL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r100_is_counter_moving(struct radeon_device *rdev, int crtc)
{
	u32 vline1, vline2;

	if (crtc == 0) {
		vline1 = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
		vline2 = (RREG32(RADEON_CRTC_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
	} else {
		vline1 = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
		vline2 = (RREG32(RADEON_CRTC2_VLINE_CRNT_VLINE) >> 16) & RADEON_CRTC_V_TOTAL;
	}
	if (vline1 != vline2)
		return true;
	else
		return false;
}