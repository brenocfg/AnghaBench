#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int accel_working; TYPE_1__ mode_info; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0007C0_CP_STAT ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_asic_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_surface_init (struct radeon_device*) ; 
 int /*<<< orphan*/  rs600_gart_disable (struct radeon_device*) ; 
 int rs600_startup (struct radeon_device*) ; 
 int /*<<< orphan*/  rv515_clock_startup (struct radeon_device*) ; 

int rs600_resume(struct radeon_device *rdev)
{
	int r;

	/* Make sur GART are not working */
	rs600_gart_disable(rdev);
	/* Resume clock before doing reset */
	rv515_clock_startup(rdev);
	/* Reset gpu before posting otherwise ATOM will enter infinite loop */
	if (radeon_asic_reset(rdev)) {
		dev_warn(rdev->dev, "GPU reset failed ! (0xE40=0x%08X, 0x7C0=0x%08X)\n",
			RREG32(R_000E40_RBBM_STATUS),
			RREG32(R_0007C0_CP_STAT));
	}
	/* post */
	atom_asic_init(rdev->mode_info.atom_context);
	/* Resume clock after posting */
	rv515_clock_startup(rdev);
	/* Initialize surface registers */
	radeon_surface_init(rdev);

	rdev->accel_working = true;
	r = rs600_startup(rdev);
	if (r) {
		rdev->accel_working = false;
	}
	return r;
}