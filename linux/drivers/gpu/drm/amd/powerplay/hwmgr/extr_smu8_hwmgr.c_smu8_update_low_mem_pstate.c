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
struct smu8_power_state {scalar_t__ action; } ;
struct TYPE_4__ {scalar_t__ nb_pstate_switch_disable; } ;
struct TYPE_3__ {scalar_t__ nb_dpm_enable; } ;
struct smu8_hwmgr {TYPE_2__ cc6_settings; TYPE_1__ sys_info; } ;
struct pp_hwmgr {struct smu8_hwmgr* backend; } ;
struct phm_set_power_state_input {int /*<<< orphan*/  pnew_state; } ;

/* Variables and functions */
 scalar_t__ CANCEL_FORCE_HIGH ; 
 scalar_t__ FORCE_HIGH ; 
 struct smu8_power_state* cast_const_smu8_power_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu8_nbdpm_pstate_enable_disable (struct pp_hwmgr*,int,int) ; 

__attribute__((used)) static int smu8_update_low_mem_pstate(struct pp_hwmgr *hwmgr, const void *input)
{
	bool disable_switch;
	bool enable_low_mem_state;
	struct smu8_hwmgr *hw_data = hwmgr->backend;
	const struct phm_set_power_state_input *states = (struct phm_set_power_state_input *)input;
	const struct smu8_power_state *pnew_state = cast_const_smu8_power_state(states->pnew_state);

	if (hw_data->sys_info.nb_dpm_enable) {
		disable_switch = hw_data->cc6_settings.nb_pstate_switch_disable ? true : false;
		enable_low_mem_state = hw_data->cc6_settings.nb_pstate_switch_disable ? false : true;

		if (pnew_state->action == FORCE_HIGH)
			smu8_nbdpm_pstate_enable_disable(hwmgr, false, disable_switch);
		else if (pnew_state->action == CANCEL_FORCE_HIGH)
			smu8_nbdpm_pstate_enable_disable(hwmgr, true, disable_switch);
		else
			smu8_nbdpm_pstate_enable_disable(hwmgr, enable_low_mem_state, disable_switch);
	}
	return 0;
}