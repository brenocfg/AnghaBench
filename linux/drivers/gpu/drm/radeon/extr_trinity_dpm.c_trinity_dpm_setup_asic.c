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
 int /*<<< orphan*/  sumo_program_sstp (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_take_smu_control (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_acquire_mutex (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_get_min_sclk_divider (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_release_mutex (struct radeon_device*) ; 

void trinity_dpm_setup_asic(struct radeon_device *rdev)
{
	trinity_acquire_mutex(rdev);
	sumo_program_sstp(rdev);
	sumo_take_smu_control(rdev, true);
	trinity_get_min_sclk_divider(rdev);
	trinity_release_mutex(rdev);
}