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
struct radeon_device {int num_crtc; } ;

/* Variables and functions */
 scalar_t__ EVERGREEN_CRTC_CONTROL ; 
 int EVERGREEN_CRTC_MASTER_EN ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__* crtc_offsets ; 
 int /*<<< orphan*/  dce4_is_counter_moving (struct radeon_device*,int) ; 
 scalar_t__ dce4_is_in_vblank (struct radeon_device*,int) ; 

void dce4_wait_for_vblank(struct radeon_device *rdev, int crtc)
{
	unsigned i = 0;

	if (crtc >= rdev->num_crtc)
		return;

	if (!(RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[crtc]) & EVERGREEN_CRTC_MASTER_EN))
		return;

	/* depending on when we hit vblank, we may be close to active; if so,
	 * wait for another frame.
	 */
	while (dce4_is_in_vblank(rdev, crtc)) {
		if (i++ % 100 == 0) {
			if (!dce4_is_counter_moving(rdev, crtc))
				break;
		}
	}

	while (!dce4_is_in_vblank(rdev, crtc)) {
		if (i++ % 100 == 0) {
			if (!dce4_is_counter_moving(rdev, crtc))
				break;
		}
	}
}