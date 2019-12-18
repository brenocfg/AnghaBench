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
struct smu_dpm_context {TYPE_2__* dpm_current_power_state; int /*<<< orphan*/  dpm_context; } ;
struct smu_context {int /*<<< orphan*/  mutex; struct smu_dpm_context smu_dpm; } ;
typedef  enum amd_pm_state_type { ____Placeholder_amd_pm_state_type } amd_pm_state_type ;
struct TYPE_3__ {int ui_label; int flags; } ;
struct TYPE_4__ {TYPE_1__ classification; } ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_STATE_TYPE_BALANCED ; 
 int POWER_STATE_TYPE_BATTERY ; 
 int POWER_STATE_TYPE_DEFAULT ; 
 int POWER_STATE_TYPE_INTERNAL_BOOT ; 
 int POWER_STATE_TYPE_PERFORMANCE ; 
 int SMU_STATE_CLASSIFICATION_FLAG_BOOT ; 
#define  SMU_STATE_UI_LABEL_BALLANCED 130 
#define  SMU_STATE_UI_LABEL_BATTERY 129 
#define  SMU_STATE_UI_LABEL_PERFORMANCE 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum
amd_pm_state_type vega20_get_current_power_state(struct smu_context *smu)
{
	enum amd_pm_state_type pm_type;
	struct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!smu_dpm_ctx->dpm_context ||
	    !smu_dpm_ctx->dpm_current_power_state)
		return -EINVAL;

	mutex_lock(&(smu->mutex));
	switch (smu_dpm_ctx->dpm_current_power_state->classification.ui_label) {
	case SMU_STATE_UI_LABEL_BATTERY:
		pm_type = POWER_STATE_TYPE_BATTERY;
		break;
	case SMU_STATE_UI_LABEL_BALLANCED:
		pm_type = POWER_STATE_TYPE_BALANCED;
		break;
	case SMU_STATE_UI_LABEL_PERFORMANCE:
		pm_type = POWER_STATE_TYPE_PERFORMANCE;
		break;
	default:
		if (smu_dpm_ctx->dpm_current_power_state->classification.flags & SMU_STATE_CLASSIFICATION_FLAG_BOOT)
			pm_type = POWER_STATE_TYPE_INTERNAL_BOOT;
		else
			pm_type = POWER_STATE_TYPE_DEFAULT;
		break;
	}
	mutex_unlock(&(smu->mutex));

	return pm_type;
}