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
struct trinity_ps {TYPE_3__* levels; } ;
struct TYPE_5__ {size_t vddc_index; size_t sclk; } ;
struct TYPE_4__ {size_t min_sclk; } ;
struct trinity_power_info {TYPE_2__ boot_pl; TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;
struct TYPE_6__ {size_t vddc_index; size_t sclk; int allow_gnb_slow; int /*<<< orphan*/  vce_wm; scalar_t__ display_wm; scalar_t__ force_nbp_state; int /*<<< orphan*/  ds_divider_index; int /*<<< orphan*/  ss_divider_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  trinity_calculate_vce_wm (struct radeon_device*,size_t) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 
 int /*<<< orphan*/  trinity_get_sleep_divider_id_from_clock (struct radeon_device*,size_t,size_t) ; 

__attribute__((used)) static void trinity_patch_thermal_state(struct radeon_device *rdev,
					struct trinity_ps *ps,
					struct trinity_ps *current_ps)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
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

	ps->levels[0].ds_divider_index =
		trinity_get_sleep_divider_id_from_clock(rdev, ps->levels[0].sclk, sclk_in_sr);
	ps->levels[0].ss_divider_index = ps->levels[0].ds_divider_index;
	ps->levels[0].allow_gnb_slow = 1;
	ps->levels[0].force_nbp_state = 0;
	ps->levels[0].display_wm = 0;
	ps->levels[0].vce_wm =
		trinity_calculate_vce_wm(rdev, ps->levels[0].sclk);
}