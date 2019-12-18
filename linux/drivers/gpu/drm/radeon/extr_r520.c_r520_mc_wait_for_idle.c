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
typedef  int uint32_t ;
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  R520_MC_STATUS ; 
 int R520_MC_STATUS_IDLE ; 
 int RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int r520_mc_wait_for_idle(struct radeon_device *rdev)
{
	unsigned i;
	uint32_t tmp;

	for (i = 0; i < rdev->usec_timeout; i++) {
		/* read MC_STATUS */
		tmp = RREG32_MC(R520_MC_STATUS);
		if (tmp & R520_MC_STATUS_IDLE) {
			return 0;
		}
		udelay(1);
	}
	return -1;
}