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
struct pp_states_info {int nums; int /*<<< orphan*/ * states; } ;
struct TYPE_2__ {int ui_label; int flags; } ;
struct pp_power_state {TYPE_1__ classification; } ;
struct pp_hwmgr {int num_ps; int ps_size; int /*<<< orphan*/  smu_lock; scalar_t__ ps; int /*<<< orphan*/  pm_en; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_BALANCED ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_BATTERY ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_DEFAULT ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_INTERNAL_BOOT ; 
 int /*<<< orphan*/  POWER_STATE_TYPE_PERFORMANCE ; 
 int PP_StateClassificationFlag_Boot ; 
#define  PP_StateUILabel_Balanced 130 
#define  PP_StateUILabel_Battery 129 
#define  PP_StateUILabel_Performance 128 
 int /*<<< orphan*/  memset (struct pp_states_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pp_dpm_get_pp_num_states(void *handle,
		struct pp_states_info *data)
{
	struct pp_hwmgr *hwmgr = handle;
	int i;

	memset(data, 0, sizeof(*data));

	if (!hwmgr || !hwmgr->pm_en ||!hwmgr->ps)
		return -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	data->nums = hwmgr->num_ps;

	for (i = 0; i < hwmgr->num_ps; i++) {
		struct pp_power_state *state = (struct pp_power_state *)
				((unsigned long)hwmgr->ps + i * hwmgr->ps_size);
		switch (state->classification.ui_label) {
		case PP_StateUILabel_Battery:
			data->states[i] = POWER_STATE_TYPE_BATTERY;
			break;
		case PP_StateUILabel_Balanced:
			data->states[i] = POWER_STATE_TYPE_BALANCED;
			break;
		case PP_StateUILabel_Performance:
			data->states[i] = POWER_STATE_TYPE_PERFORMANCE;
			break;
		default:
			if (state->classification.flags & PP_StateClassificationFlag_Boot)
				data->states[i] = POWER_STATE_TYPE_INTERNAL_BOOT;
			else
				data->states[i] = POWER_STATE_TYPE_DEFAULT;
		}
	}
	mutex_unlock(&hwmgr->smu_lock);
	return 0;
}