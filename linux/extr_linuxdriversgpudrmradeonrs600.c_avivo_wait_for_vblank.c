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
 int AVIVO_CRTC_EN ; 
 scalar_t__ AVIVO_D1CRTC_CONTROL ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  avivo_is_counter_moving (struct radeon_device*,int) ; 
 scalar_t__ avivo_is_in_vblank (struct radeon_device*,int) ; 
 scalar_t__* crtc_offsets ; 

void avivo_wait_for_vblank(struct radeon_device *rdev, int crtc)
{
	unsigned i = 0;

	if (crtc >= rdev->num_crtc)
		return;

	if (!(RREG32(AVIVO_D1CRTC_CONTROL + crtc_offsets[crtc]) & AVIVO_CRTC_EN))
		return;

	/* depending on when we hit vblank, we may be close to active; if so,
	 * wait for another frame.
	 */
	while (avivo_is_in_vblank(rdev, crtc)) {
		if (i++ % 100 == 0) {
			if (!avivo_is_counter_moving(rdev, crtc))
				break;
		}
	}

	while (!avivo_is_in_vblank(rdev, crtc)) {
		if (i++ % 100 == 0) {
			if (!avivo_is_counter_moving(rdev, crtc))
				break;
		}
	}
}