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
struct radeon_device {int flags; } ;

/* Variables and functions */
 int GFX_POWER_GATING_ENABLE ; 
 int GFX_POWER_GATING_SRC ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  RLC_CNTL ; 
 int RLC_ENABLE ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void evergreen_rlc_start(struct radeon_device *rdev)
{
	u32 mask = RLC_ENABLE;

	if (rdev->flags & RADEON_IS_IGP) {
		mask |= GFX_POWER_GATING_ENABLE | GFX_POWER_GATING_SRC;
	}

	WREG32(RLC_CNTL, mask);
}