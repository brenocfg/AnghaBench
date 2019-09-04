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
struct sumo_ps {int dummy; } ;
struct radeon_ps {struct sumo_ps* ps_priv; } ;
struct sumo_power_info {struct sumo_ps current_ps; struct radeon_ps current_rps; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void sumo_update_current_ps(struct radeon_device *rdev,
				   struct radeon_ps *rps)
{
	struct sumo_ps *new_ps = sumo_get_ps(rps);
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	pi->current_rps = *rps;
	pi->current_ps = *new_ps;
	pi->current_rps.ps_priv = &pi->current_ps;
}