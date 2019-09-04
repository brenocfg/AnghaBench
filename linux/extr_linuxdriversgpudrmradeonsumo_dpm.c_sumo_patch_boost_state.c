#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sumo_ps {int flags; int num_levels; TYPE_2__* levels; } ;
struct TYPE_3__ {int /*<<< orphan*/  sclk_dpm_tdp_limit_boost; int /*<<< orphan*/  boost_vid_2bit; int /*<<< orphan*/  boost_sclk; } ;
struct TYPE_4__ {int /*<<< orphan*/  sclk_dpm_tdp_limit; int /*<<< orphan*/  vddc_index; int /*<<< orphan*/  sclk; } ;
struct sumo_power_info {TYPE_1__ sys_info; TYPE_2__ boost_pl; } ;
struct radeon_ps {int dummy; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int SUMO_POWERSTATE_FLAGS_BOOST_STATE ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 struct sumo_ps* sumo_get_ps (struct radeon_ps*) ; 

__attribute__((used)) static void sumo_patch_boost_state(struct radeon_device *rdev,
				   struct radeon_ps *rps)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	struct sumo_ps *new_ps = sumo_get_ps(rps);

	if (new_ps->flags & SUMO_POWERSTATE_FLAGS_BOOST_STATE) {
		pi->boost_pl = new_ps->levels[new_ps->num_levels - 1];
		pi->boost_pl.sclk = pi->sys_info.boost_sclk;
		pi->boost_pl.vddc_index = pi->sys_info.boost_vid_2bit;
		pi->boost_pl.sclk_dpm_tdp_limit = pi->sys_info.sclk_dpm_tdp_limit_boost;
	}
}