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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0060A4_D1CRTC_STATUS_FRAME_COUNT ; 
 int /*<<< orphan*/  R_0068A4_D2CRTC_STATUS_FRAME_COUNT ; 

u32 rs600_get_vblank_counter(struct radeon_device *rdev, int crtc)
{
	if (crtc == 0)
		return RREG32(R_0060A4_D1CRTC_STATUS_FRAME_COUNT);
	else
		return RREG32(R_0068A4_D2CRTC_STATUS_FRAME_COUNT);
}