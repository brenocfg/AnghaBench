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
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  hard_min_level; int /*<<< orphan*/  soft_max_level; int /*<<< orphan*/  soft_min_level; } ;
struct vega20_single_dpm_table {size_t count; TYPE_2__* dpm_levels; TYPE_1__ dpm_state; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table dcef_table; struct vega20_single_dpm_table fclk_table; struct vega20_single_dpm_table soc_table; struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table gfx_table; } ;
struct smu_dpm_context {scalar_t__ dpm_level; struct vega20_dpm_table* dpm_context; } ;
struct smu_context {int /*<<< orphan*/  mutex; struct smu_dpm_context smu_dpm; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ AMD_DPM_FORCED_LEVEL_MANUAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  FEATURE_DPM_DCEFCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_FCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_GFXCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_SOCCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_UCLK_MASK ; 
 size_t NUM_LINK_LEVELS ; 
#define  SMU_DCEFCLK 133 
#define  SMU_FCLK 132 
#define  SMU_MCLK 131 
 int /*<<< orphan*/  SMU_MSG_SetMinLinkDpmByIndex ; 
#define  SMU_PCIE 130 
#define  SMU_SCLK 129 
#define  SMU_SOCCLK 128 
 size_t ffs (size_t) ; 
 size_t fls (size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,size_t) ; 
 int vega20_upload_dpm_level (struct smu_context*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_force_clk_levels(struct smu_context *smu,
			enum  smu_clk_type clk_type, uint32_t mask)
{
	struct vega20_dpm_table *dpm_table;
	struct vega20_single_dpm_table *single_dpm_table;
	uint32_t soft_min_level, soft_max_level, hard_min_level;
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	int ret = 0;

	if (smu_dpm->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) {
		pr_info("force clock level is for dpm manual mode only.\n");
		return -EINVAL;
	}

	mutex_lock(&(smu->mutex));

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	dpm_table = smu->smu_dpm.dpm_context;

	switch (clk_type) {
	case SMU_SCLK:
		single_dpm_table = &(dpm_table->gfx_table);

		if (soft_max_level >= single_dpm_table->count) {
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			break;
		}

		single_dpm_table->dpm_state.soft_min_level =
			single_dpm_table->dpm_levels[soft_min_level].value;
		single_dpm_table->dpm_state.soft_max_level =
			single_dpm_table->dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_level(smu, false, FEATURE_DPM_GFXCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = vega20_upload_dpm_level(smu, true, FEATURE_DPM_GFXCLK_MASK);
		if (ret)
			pr_err("Failed to upload dpm max level to highest!\n");

		break;

	case SMU_MCLK:
		single_dpm_table = &(dpm_table->mem_table);

		if (soft_max_level >= single_dpm_table->count) {
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			break;
		}

		single_dpm_table->dpm_state.soft_min_level =
			single_dpm_table->dpm_levels[soft_min_level].value;
		single_dpm_table->dpm_state.soft_max_level =
			single_dpm_table->dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_level(smu, false, FEATURE_DPM_UCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = vega20_upload_dpm_level(smu, true, FEATURE_DPM_UCLK_MASK);
		if (ret)
			pr_err("Failed to upload dpm max level to highest!\n");

		break;

	case SMU_SOCCLK:
		single_dpm_table = &(dpm_table->soc_table);

		if (soft_max_level >= single_dpm_table->count) {
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			break;
		}

		single_dpm_table->dpm_state.soft_min_level =
			single_dpm_table->dpm_levels[soft_min_level].value;
		single_dpm_table->dpm_state.soft_max_level =
			single_dpm_table->dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_level(smu, false, FEATURE_DPM_SOCCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = vega20_upload_dpm_level(smu, true, FEATURE_DPM_SOCCLK_MASK);
		if (ret)
			pr_err("Failed to upload dpm max level to highest!\n");

		break;

	case SMU_FCLK:
		single_dpm_table = &(dpm_table->fclk_table);

		if (soft_max_level >= single_dpm_table->count) {
			pr_err("Clock level specified %d is over max allowed %d\n",
					soft_max_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			break;
		}

		single_dpm_table->dpm_state.soft_min_level =
			single_dpm_table->dpm_levels[soft_min_level].value;
		single_dpm_table->dpm_state.soft_max_level =
			single_dpm_table->dpm_levels[soft_max_level].value;

		ret = vega20_upload_dpm_level(smu, false, FEATURE_DPM_FCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = vega20_upload_dpm_level(smu, true, FEATURE_DPM_FCLK_MASK);
		if (ret)
			pr_err("Failed to upload dpm max level to highest!\n");

		break;

	case SMU_DCEFCLK:
		hard_min_level = soft_min_level;
		single_dpm_table = &(dpm_table->dcef_table);

		if (hard_min_level >= single_dpm_table->count) {
			pr_err("Clock level specified %d is over max allowed %d\n",
					hard_min_level, single_dpm_table->count - 1);
			ret = -EINVAL;
			break;
		}

		single_dpm_table->dpm_state.hard_min_level =
			single_dpm_table->dpm_levels[hard_min_level].value;

		ret = vega20_upload_dpm_level(smu, false, FEATURE_DPM_DCEFCLK_MASK);
		if (ret)
			pr_err("Failed to upload boot level to lowest!\n");

		break;

	case SMU_PCIE:
		if (soft_min_level >= NUM_LINK_LEVELS ||
		    soft_max_level >= NUM_LINK_LEVELS) {
			ret = -EINVAL;
			break;
		}

		ret = smu_send_smc_msg_with_param(smu,
				SMU_MSG_SetMinLinkDpmByIndex, soft_min_level);
		if (ret)
			pr_err("Failed to set min link dpm level!\n");

		break;

	default:
		break;
	}

	mutex_unlock(&(smu->mutex));
	return ret;
}