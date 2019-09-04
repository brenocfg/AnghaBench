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
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_INT_REQ ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void trinity_acquire_mutex(struct radeon_device *rdev)
{
	int i;

	WREG32(SMC_INT_REQ, 1);
	for (i = 0; i < rdev->usec_timeout; i++) {
		if ((RREG32(SMC_INT_REQ) & 0xffff) == 1)
			break;
		udelay(1);
	}
}