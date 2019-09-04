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
struct radeon_ps {int dummy; } ;
struct sumo_power_info {struct radeon_ps requested_rps; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_update_current_ps (struct radeon_device*,struct radeon_ps*) ; 

void sumo_dpm_post_set_power_state(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct radeon_ps *new_ps = &pi->requested_rps;

	sumo_update_current_ps(rdev, new_ps);
}