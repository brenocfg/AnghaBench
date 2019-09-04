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
struct smu8_power_state {int level; TYPE_1__* levels; } ;
struct pp_power_state {int /*<<< orphan*/  hardware; } ;
struct pp_hwmgr {struct pp_power_state* request_ps; } ;
struct TYPE_2__ {int /*<<< orphan*/  engineClock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct smu8_power_state* cast_smu8_power_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t smu8_dpm_get_sclk(struct pp_hwmgr *hwmgr, bool low)
{
	struct pp_power_state  *ps;
	struct smu8_power_state  *smu8_ps;

	if (hwmgr == NULL)
		return -EINVAL;

	ps = hwmgr->request_ps;

	if (ps == NULL)
		return -EINVAL;

	smu8_ps = cast_smu8_power_state(&ps->hardware);

	if (low)
		return smu8_ps->levels[0].engineClock;
	else
		return smu8_ps->levels[smu8_ps->level-1].engineClock;
}