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
struct radeon_ring {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_000E40_GUI_ACTIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000E40_RBBM_STATUS ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_device*,struct radeon_ring*) ; 
 int radeon_ring_test_lockup (struct radeon_device*,struct radeon_ring*) ; 

bool r100_gpu_is_lockup(struct radeon_device *rdev, struct radeon_ring *ring)
{
	u32 rbbm_status;

	rbbm_status = RREG32(R_000E40_RBBM_STATUS);
	if (!G_000E40_GUI_ACTIVE(rbbm_status)) {
		radeon_ring_lockup_update(rdev, ring);
		return false;
	}
	return radeon_ring_test_lockup(rdev, ring);
}