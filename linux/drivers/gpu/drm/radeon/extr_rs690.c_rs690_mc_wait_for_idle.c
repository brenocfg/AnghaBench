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
typedef  int /*<<< orphan*/  uint32_t ;
struct radeon_device {unsigned int usec_timeout; } ;

/* Variables and functions */
 scalar_t__ G_000090_MC_SYSTEM_IDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32_MC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_000090_MC_SYSTEM_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 

int rs690_mc_wait_for_idle(struct radeon_device *rdev)
{
	unsigned i;
	uint32_t tmp;

	for (i = 0; i < rdev->usec_timeout; i++) {
		/* read MC_STATUS */
		tmp = RREG32_MC(R_000090_MC_SYSTEM_STATUS);
		if (G_000090_MC_SYSTEM_IDLE(tmp))
			return 0;
		udelay(1);
	}
	return -1;
}