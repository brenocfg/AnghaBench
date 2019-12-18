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
 int RADEON_RBBM_ACTIVE ; 
 int /*<<< orphan*/  RADEON_RBBM_STATUS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ r100_rbbm_fifo_wait_for_entry (struct radeon_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int r100_gui_wait_for_idle(struct radeon_device *rdev)
{
	unsigned i;
	uint32_t tmp;

	if (r100_rbbm_fifo_wait_for_entry(rdev, 64)) {
		pr_warn("radeon: wait for empty RBBM fifo failed! Bad things might happen.\n");
	}
	for (i = 0; i < rdev->usec_timeout; i++) {
		tmp = RREG32(RADEON_RBBM_STATUS);
		if (!(tmp & RADEON_RBBM_ACTIVE)) {
			return 0;
		}
		udelay(1);
	}
	return -1;
}