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
typedef  size_t u32 ;
struct trinity_power_info {int /*<<< orphan*/ * at; } ;
struct trinity_pl {int /*<<< orphan*/  vce_wm; int /*<<< orphan*/  display_wm; int /*<<< orphan*/  force_nbp_state; int /*<<< orphan*/  allow_gnb_slow; int /*<<< orphan*/  ds_divider_index; int /*<<< orphan*/  ss_divider_index; int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 size_t SUMO_MAX_HARDWARE_POWERLEVELS ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_set_allos_gnb_slow (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_at (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_display_wm (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_divider_value (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_ds_dividers (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_force_nbp_state (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_ss_dividers (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_vce_wm (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trinity_set_vid (struct radeon_device*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trinity_program_power_level(struct radeon_device *rdev,
					struct trinity_pl *pl, u32 index)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);

	if (index >= SUMO_MAX_HARDWARE_POWERLEVELS)
		return;

	trinity_set_divider_value(rdev, index, pl->sclk);
	trinity_set_vid(rdev, index, pl->vddc_index);
	trinity_set_ss_dividers(rdev, index, pl->ss_divider_index);
	trinity_set_ds_dividers(rdev, index, pl->ds_divider_index);
	trinity_set_allos_gnb_slow(rdev, index, pl->allow_gnb_slow);
	trinity_set_force_nbp_state(rdev, index, pl->force_nbp_state);
	trinity_set_display_wm(rdev, index, pl->display_wm);
	trinity_set_vce_wm(rdev, index, pl->vce_wm);
	trinity_set_at(rdev, index, pi->at[index]);
}