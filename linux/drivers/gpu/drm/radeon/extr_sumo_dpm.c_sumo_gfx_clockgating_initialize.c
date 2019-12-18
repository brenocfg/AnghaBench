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
 int /*<<< orphan*/  sumo_program_git (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_program_grsd (struct radeon_device*) ; 

void sumo_gfx_clockgating_initialize(struct radeon_device *rdev)
{
	sumo_program_git(rdev);
	sumo_program_grsd(rdev);
}