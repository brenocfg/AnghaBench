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
struct TYPE_2__ {int ui_label; int flags; } ;
struct pp_power_state {TYPE_1__ classification; } ;
struct pp_hwmgr {int /*<<< orphan*/  smu_lock; struct pp_power_state* current_ps; int /*<<< orphan*/  pm_en; } ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_STATE_TYPE_BALANCED ; 
 int POWER_STATE_TYPE_BATTERY ; 
 int POWER_STATE_TYPE_DEFAULT ; 
 int POWER_STATE_TYPE_INTERNAL_BOOT ; 
 int POWER_STATE_TYPE_PERFORMANCE ; 
 int PP_StateClassificationFlag_Boot ; 
#define  PP_StateUILabel_Balanced 130 
#define  PP_StateUILabel_Battery 129 
#define  PP_StateUILabel_Performance 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum amd_pm_state_type pp_dpm_get_current_power_state(void *handle)
{
	struct pp_hwmgr *hwmgr = handle;
	struct pp_power_state *state;
	enum amd_pm_state_type pm_type;

	if (!hwmgr || !hwmgr->pm_en || !hwmgr->current_ps)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	state = hwmgr->current_ps;

	switch (state->classification.ui_label) {
	case PP_StateUILabel_Battery:
		pm_type = POWER_STATE_TYPE_BATTERY;
		break;
	case PP_StateUILabel_Balanced:
		pm_type = POWER_STATE_TYPE_BALANCED;
		break;
	case PP_StateUILabel_Performance:
		pm_type = POWER_STATE_TYPE_PERFORMANCE;
		break;
	default:
		if (state->classification.flags & PP_StateClassificationFlag_Boot)
			pm_type = POWER_STATE_TYPE_INTERNAL_BOOT;
		else
			pm_type = POWER_STATE_TYPE_DEFAULT;
		break;
	}
	mutex_unlock(&hwmgr->smu_lock);

	return pm_type;
}