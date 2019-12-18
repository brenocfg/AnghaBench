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
struct trinity_power_info {scalar_t__ enable_gfx_power_gating; scalar_t__ enable_gfx_dynamic_mgpg; scalar_t__ enable_gfx_clock_gating; scalar_t__ enable_mg_clock_gating; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sumo_gfx_clockgating_initialize (struct radeon_device*) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_gfx_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_gfx_dynamic_mgpg_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_gfx_powergating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_gfx_powergating_initialize (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_ls_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_mg_clockgating_enable (struct radeon_device*,int) ; 
 int /*<<< orphan*/  trinity_mg_clockgating_initialize (struct radeon_device*) ; 

__attribute__((used)) static void trinity_enable_clock_power_gating(struct radeon_device *rdev)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (pi->enable_gfx_clock_gating)
		sumo_gfx_clockgating_initialize(rdev);
	if (pi->enable_mg_clock_gating)
		trinity_mg_clockgating_initialize(rdev);
	if (pi->enable_gfx_power_gating)
		trinity_gfx_powergating_initialize(rdev);
	if (pi->enable_mg_clock_gating) {
		trinity_ls_clockgating_enable(rdev, true);
		trinity_mg_clockgating_enable(rdev, true);
	}
	if (pi->enable_gfx_clock_gating)
		trinity_gfx_clockgating_enable(rdev, true);
	if (pi->enable_gfx_dynamic_mgpg)
		trinity_gfx_dynamic_mgpg_enable(rdev, true);
	if (pi->enable_gfx_power_gating)
		trinity_gfx_powergating_enable(rdev, true);
}