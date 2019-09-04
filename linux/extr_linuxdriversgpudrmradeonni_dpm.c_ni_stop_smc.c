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
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  LB_SYNC_RESET_SEL ; 
 int LB_SYNC_RESET_SEL_MASK ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r7xx_stop_smc (struct radeon_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ni_stop_smc(struct radeon_device *rdev)
{
	u32 tmp;
	int i;

	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(LB_SYNC_RESET_SEL) & LB_SYNC_RESET_SEL_MASK;
		if (tmp != 1)
			break;
		udelay(1);
	}

	udelay(100);

	r7xx_stop_smc(rdev);
}