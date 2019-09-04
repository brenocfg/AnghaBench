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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_MC_STATUS ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 scalar_t__ rs400_mc_wait_for_idle (struct radeon_device*) ; 

__attribute__((used)) static void rs400_gpu_init(struct radeon_device *rdev)
{
	/* FIXME: is this correct ? */
	r420_pipes_init(rdev);
	if (rs400_mc_wait_for_idle(rdev)) {
		pr_warn("rs400: Failed to wait MC idle while programming pipes. Bad things might happen. %08x\n",
			RREG32(RADEON_MC_STATUS));
	}
}