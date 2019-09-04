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
typedef  int /*<<< orphan*/  uint32_t ;
struct smu7_power_state {int performance_level_count; TYPE_1__* performance_levels; } ;
struct pp_power_state {int /*<<< orphan*/  hardware; } ;
struct pp_hwmgr {struct pp_power_state* request_ps; } ;
struct TYPE_2__ {int /*<<< orphan*/  engine_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct smu7_power_state* cast_phw_smu7_power_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t smu7_dpm_get_sclk(struct pp_hwmgr *hwmgr, bool low)
{
	struct pp_power_state  *ps;
	struct smu7_power_state  *smu7_ps;

	if (hwmgr == NULL)
		return -EINVAL;

	ps = hwmgr->request_ps;

	if (ps == NULL)
		return -EINVAL;

	smu7_ps = cast_phw_smu7_power_state(&ps->hardware);

	if (low)
		return smu7_ps->performance_levels[0].engine_clock;
	else
		return smu7_ps->performance_levels
				[smu7_ps->performance_level_count-1].engine_clock;
}