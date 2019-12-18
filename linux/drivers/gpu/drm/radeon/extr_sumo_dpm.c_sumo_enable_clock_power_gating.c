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
struct sumo_power_info {scalar_t__ enable_gfx_power_gating; scalar_t__ enable_gfx_clock_gating; scalar_t__ enable_mg_clock_gating; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  sumo_gfx_clockgating_initialize (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_gfx_powergating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  sumo_gfx_powergating_initialize (struct radeon_device*) ; 
 int /*<<< orphan*/  sumo_mg_clockgating_enable (struct radeon_device*,int) ; 

__attribute__((used)) static int sumo_enable_clock_power_gating(struct radeon_device *rdev)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);

	if (pi->enable_gfx_clock_gating)
		sumo_gfx_clockgating_initialize(rdev);
	if (pi->enable_gfx_power_gating)
		sumo_gfx_powergating_initialize(rdev);
	if (pi->enable_mg_clock_gating)
		sumo_mg_clockgating_enable(rdev, true);
	if (pi->enable_gfx_clock_gating)
		sumo_gfx_clockgating_enable(rdev, true);
	if (pi->enable_gfx_power_gating)
		sumo_gfx_powergating_enable(rdev, true);

	return 0;
}