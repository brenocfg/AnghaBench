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
typedef  int uint32_t ;
struct TYPE_4__ {int soft_max_level; int soft_min_level; int hard_min_level; } ;
struct vega20_single_dpm_table {TYPE_2__ dpm_state; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table dcef_table; struct vega20_single_dpm_table fclk_table; struct vega20_single_dpm_table soc_table; struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; } ;
struct TYPE_3__ {struct vega20_dpm_table* dpm_context; } ;
struct smu_context {TYPE_1__ smu_dpm; } ;

/* Variables and functions */
 int FEATURE_DPM_DCEFCLK_MASK ; 
 int FEATURE_DPM_FCLK_MASK ; 
 int FEATURE_DPM_GFXCLK_MASK ; 
 int FEATURE_DPM_SOCCLK_MASK ; 
 int FEATURE_DPM_UCLK_MASK ; 
 int PPCLK_DCEFCLK ; 
 int PPCLK_FCLK ; 
 int PPCLK_GFXCLK ; 
 int PPCLK_SOCCLK ; 
 int PPCLK_UCLK ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_DCEFCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_FCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_GFXCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_SOCCLK_BIT ; 
 int /*<<< orphan*/  SMU_FEATURE_DPM_UCLK_BIT ; 
 int /*<<< orphan*/  SMU_MSG_SetHardMinByFreq ; 
 int /*<<< orphan*/  SMU_MSG_SetSoftMaxByFreq ; 
 int /*<<< orphan*/  SMU_MSG_SetSoftMinByFreq ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vega20_upload_dpm_level(struct smu_context *smu, bool max,
				   uint32_t feature_mask)
{
	struct vega20_dpm_table *dpm_table;
	struct vega20_single_dpm_table *single_dpm_table;
	uint32_t freq;
	int ret = 0;

	dpm_table = smu->smu_dpm.dpm_context;

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_GFXCLK_MASK)) {
		single_dpm_table = &(dpm_table->gfx_table);
		freq = max ? single_dpm_table->dpm_state.soft_max_level :
			single_dpm_table->dpm_state.soft_min_level;
		ret = smu_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_GFXCLK << 16) | (freq & 0xffff));
		if (ret) {
			pr_err("Failed to set soft %s gfxclk !\n",
						max ? "max" : "min");
			return ret;
		}
	}

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_UCLK_MASK)) {
		single_dpm_table = &(dpm_table->mem_table);
		freq = max ? single_dpm_table->dpm_state.soft_max_level :
			single_dpm_table->dpm_state.soft_min_level;
		ret = smu_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_UCLK << 16) | (freq & 0xffff));
		if (ret) {
			pr_err("Failed to set soft %s memclk !\n",
						max ? "max" : "min");
			return ret;
		}
	}

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_SOCCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_SOCCLK_MASK)) {
		single_dpm_table = &(dpm_table->soc_table);
		freq = max ? single_dpm_table->dpm_state.soft_max_level :
			single_dpm_table->dpm_state.soft_min_level;
		ret = smu_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_SOCCLK << 16) | (freq & 0xffff));
		if (ret) {
			pr_err("Failed to set soft %s socclk !\n",
						max ? "max" : "min");
			return ret;
		}
	}

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_FCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_FCLK_MASK)) {
		single_dpm_table = &(dpm_table->fclk_table);
		freq = max ? single_dpm_table->dpm_state.soft_max_level :
			single_dpm_table->dpm_state.soft_min_level;
		ret = smu_send_smc_msg_with_param(smu,
			(max ? SMU_MSG_SetSoftMaxByFreq : SMU_MSG_SetSoftMinByFreq),
			(PPCLK_FCLK << 16) | (freq & 0xffff));
		if (ret) {
			pr_err("Failed to set soft %s fclk !\n",
						max ? "max" : "min");
			return ret;
		}
	}

	if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_DCEFCLK_BIT) &&
	    (feature_mask & FEATURE_DPM_DCEFCLK_MASK)) {
		single_dpm_table = &(dpm_table->dcef_table);
		freq = single_dpm_table->dpm_state.hard_min_level;
		if (!max) {
			ret = smu_send_smc_msg_with_param(smu,
				SMU_MSG_SetHardMinByFreq,
				(PPCLK_DCEFCLK << 16) | (freq & 0xffff));
			if (ret) {
				pr_err("Failed to set hard min dcefclk !\n");
				return ret;
			}
		}
	}

	return ret;
}