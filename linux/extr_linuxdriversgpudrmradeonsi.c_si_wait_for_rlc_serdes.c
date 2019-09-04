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
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLC_SERDES_MASTER_BUSY_0 ; 
 int /*<<< orphan*/  RLC_SERDES_MASTER_BUSY_1 ; 
 scalar_t__ RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void si_wait_for_rlc_serdes(struct radeon_device *rdev)
{
	int i;

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(RLC_SERDES_MASTER_BUSY_0) == 0)
			break;
		udelay(1);
	}

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(RLC_SERDES_MASTER_BUSY_1) == 0)
			break;
		udelay(1);
	}
}