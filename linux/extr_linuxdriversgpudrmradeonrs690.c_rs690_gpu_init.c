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
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  r420_pipes_init (struct radeon_device*) ; 
 scalar_t__ rs690_mc_wait_for_idle (struct radeon_device*) ; 

__attribute__((used)) static void rs690_gpu_init(struct radeon_device *rdev)
{
	/* FIXME: is this correct ? */
	r420_pipes_init(rdev);
	if (rs690_mc_wait_for_idle(rdev)) {
		pr_warn("Failed to wait MC idle while programming pipes. Bad things might happen.\n");
	}
}