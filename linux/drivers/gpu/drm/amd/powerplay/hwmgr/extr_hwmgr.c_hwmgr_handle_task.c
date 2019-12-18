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
struct pp_power_state {int dummy; } ;
struct pp_hwmgr {int dummy; } ;
typedef  enum amd_pp_task { ____Placeholder_amd_pp_task } amd_pp_task ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;
typedef  enum PP_StateUILabel { ____Placeholder_PP_StateUILabel } PP_StateUILabel ;

/* Variables and functions */
#define  AMD_PP_TASK_COMPLETE_INIT 131 
#define  AMD_PP_TASK_DISPLAY_CONFIG_CHANGE 130 
#define  AMD_PP_TASK_ENABLE_USER_STATE 129 
#define  AMD_PP_TASK_READJUST_POWER_STATE 128 
 int EINVAL ; 
 int phm_pre_display_configuration_changed (struct pp_hwmgr*) ; 
 int phm_set_cpu_power_state (struct pp_hwmgr*) ; 
 int power_state_convert (int) ; 
 int psm_adjust_power_state_dynamic (struct pp_hwmgr*,int,struct pp_power_state*) ; 
 int psm_set_performance_states (struct pp_hwmgr*) ; 
 int psm_set_user_performance_state (struct pp_hwmgr*,int,struct pp_power_state**) ; 

int hwmgr_handle_task(struct pp_hwmgr *hwmgr, enum amd_pp_task task_id,
		enum amd_pm_state_type *user_state)
{
	int ret = 0;

	if (hwmgr == NULL)
		return -EINVAL;

	switch (task_id) {
	case AMD_PP_TASK_DISPLAY_CONFIG_CHANGE:
		ret = phm_pre_display_configuration_changed(hwmgr);
		if (ret)
			return ret;
		ret = phm_set_cpu_power_state(hwmgr);
		if (ret)
			return ret;
		ret = psm_set_performance_states(hwmgr);
		if (ret)
			return ret;
		ret = psm_adjust_power_state_dynamic(hwmgr, false, NULL);
		break;
	case AMD_PP_TASK_ENABLE_USER_STATE:
	{
		enum PP_StateUILabel requested_ui_label;
		struct pp_power_state *requested_ps = NULL;

		if (user_state == NULL) {
			ret = -EINVAL;
			break;
		}

		requested_ui_label = power_state_convert(*user_state);
		ret = psm_set_user_performance_state(hwmgr, requested_ui_label, &requested_ps);
		if (ret)
			return ret;
		ret = psm_adjust_power_state_dynamic(hwmgr, true, requested_ps);
		break;
	}
	case AMD_PP_TASK_COMPLETE_INIT:
	case AMD_PP_TASK_READJUST_POWER_STATE:
		ret = psm_adjust_power_state_dynamic(hwmgr, true, NULL);
		break;
	default:
		break;
	}
	return ret;
}