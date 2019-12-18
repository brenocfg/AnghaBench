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
struct smu8_power_state {int level; int /*<<< orphan*/ * levels; scalar_t__ bapm_flags; scalar_t__ nbps_flags; } ;
struct smu8_hwmgr {int /*<<< orphan*/  boot_power_level; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;
struct pp_hw_power_state {int dummy; } ;

/* Variables and functions */
 struct smu8_power_state* cast_smu8_power_state (struct pp_hw_power_state*) ; 

__attribute__((used)) static int smu8_dpm_patch_boot_state(struct pp_hwmgr *hwmgr,
					struct pp_hw_power_state *hw_ps)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct smu8_power_state *smu8_ps = cast_smu8_power_state(hw_ps);

	smu8_ps->level = 1;
	smu8_ps->nbps_flags = 0;
	smu8_ps->bapm_flags = 0;
	smu8_ps->levels[0] = data->boot_power_level;

	return 0;
}