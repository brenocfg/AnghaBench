#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smu10_power_state {int level; TYPE_1__* levels; } ;
struct pp_hwmgr {int dummy; } ;
struct pp_hw_power_state {int dummy; } ;
struct pp_clock_info {int min_eng_clk; int max_eng_clk; } ;
struct TYPE_2__ {int engine_clock; int ss_divider_index; } ;

/* Variables and functions */
 struct smu10_power_state* cast_const_smu10_ps (struct pp_hw_power_state const*) ; 

__attribute__((used)) static int smu10_get_current_shallow_sleep_clocks(struct pp_hwmgr *hwmgr,
	const struct pp_hw_power_state *state, struct pp_clock_info *clock_info)
{
	const struct smu10_power_state *ps = cast_const_smu10_ps(state);

	clock_info->min_eng_clk = ps->levels[0].engine_clock / (1 << (ps->levels[0].ss_divider_index));
	clock_info->max_eng_clk = ps->levels[ps->level - 1].engine_clock / (1 << (ps->levels[ps->level - 1].ss_divider_index));

	return 0;
}