#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sumo_ps {TYPE_3__* levels; } ;
struct TYPE_5__ {size_t vddc_index; size_t sclk; } ;
struct TYPE_4__ {size_t min_sclk; } ;
struct sumo_power_info {TYPE_2__ boot_pl; TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;
struct TYPE_6__ {size_t vddc_index; size_t sclk; scalar_t__ ss_divider_index; scalar_t__ ds_divider_index; } ;

/* Variables and functions */
 size_t SUMO_MINIMUM_ENGINE_CLOCK ; 
 struct sumo_power_info* sumo_get_pi (struct radeon_device*) ; 
 void* sumo_get_sleep_divider_id_from_clock (struct radeon_device*,size_t,size_t) ; 

__attribute__((used)) static void sumo_patch_thermal_state(struct radeon_device *rdev,
				     struct sumo_ps *ps,
				     struct sumo_ps *current_ps)
{
	struct sumo_power_info *pi = sumo_get_pi(rdev);
	u32 sclk_in_sr = pi->sys_info.min_sclk; /* ??? */
	u32 current_vddc;
	u32 current_sclk;
	u32 current_index = 0;

	if (current_ps) {
		current_vddc = current_ps->levels[current_index].vddc_index;
		current_sclk = current_ps->levels[current_index].sclk;
	} else {
		current_vddc = pi->boot_pl.vddc_index;
		current_sclk = pi->boot_pl.sclk;
	}

	ps->levels[0].vddc_index = current_vddc;

	if (ps->levels[0].sclk > current_sclk)
		ps->levels[0].sclk = current_sclk;

	ps->levels[0].ss_divider_index =
		sumo_get_sleep_divider_id_from_clock(rdev, ps->levels[0].sclk, sclk_in_sr);

	ps->levels[0].ds_divider_index =
		sumo_get_sleep_divider_id_from_clock(rdev, ps->levels[0].sclk, SUMO_MINIMUM_ENGINE_CLOCK);

	if (ps->levels[0].ds_divider_index > ps->levels[0].ss_divider_index + 1)
		ps->levels[0].ds_divider_index = ps->levels[0].ss_divider_index + 1;

	if (ps->levels[0].ss_divider_index == ps->levels[0].ds_divider_index) {
		if (ps->levels[0].ss_divider_index > 1)
			ps->levels[0].ss_divider_index = ps->levels[0].ss_divider_index - 1;
	}

	if (ps->levels[0].ss_divider_index == 0)
		ps->levels[0].ds_divider_index = 0;

	if (ps->levels[0].ds_divider_index == 0)
		ps->levels[0].ss_divider_index = 0;
}