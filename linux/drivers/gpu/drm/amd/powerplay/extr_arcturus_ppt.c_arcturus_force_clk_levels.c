#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {struct arcturus_dpm_table* dpm_context; } ;
struct smu_context {int /*<<< orphan*/  mutex; TYPE_1__ smu_dpm; } ;
struct TYPE_5__ {int /*<<< orphan*/  soft_max_level; int /*<<< orphan*/  soft_min_level; } ;
struct arcturus_single_dpm_table {size_t count; TYPE_3__* dpm_levels; TYPE_2__ dpm_state; } ;
struct arcturus_dpm_table {struct arcturus_single_dpm_table fclk_table; struct arcturus_single_dpm_table soc_table; struct arcturus_single_dpm_table mem_table; struct arcturus_single_dpm_table gfx_table; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FEATURE_DPM_FCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_GFXCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_SOCCLK_MASK ; 
 int /*<<< orphan*/  FEATURE_DPM_UCLK_MASK ; 
#define  SMU_FCLK 131 
#define  SMU_MCLK 130 
#define  SMU_SCLK 129 
#define  SMU_SOCCLK 128 
 int arcturus_upload_dpm_level (struct smu_context*,int,int /*<<< orphan*/ ) ; 
 size_t ffs (size_t) ; 
 size_t fls (size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int arcturus_force_clk_levels(struct smu_context *smu,
			enum smu_clk_type type, uint32_t mask)
{
	struct arcturus_dpm_table *dpm_table;
	struct arcturus_single_dpm_table *single_dpm_table;
	uint32_t soft_min_level, soft_max_level;
	int ret = 0;

	mutex_lock(&(smu->mutex));

	soft_min_level = mask ? (ffs(mask) - 1) : 0;
	soft_max_level = mask ? (fls(mask) - 1) : 0;

	dpm_table = smu->smu_dpm.dpm_context;

	switch (type) {
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

		ret = arcturus_upload_dpm_level(smu, false, FEATURE_DPM_GFXCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = arcturus_upload_dpm_level(smu, true, FEATURE_DPM_GFXCLK_MASK);
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

		ret = arcturus_upload_dpm_level(smu, false, FEATURE_DPM_UCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = arcturus_upload_dpm_level(smu, true, FEATURE_DPM_UCLK_MASK);
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

		ret = arcturus_upload_dpm_level(smu, false, FEATURE_DPM_SOCCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = arcturus_upload_dpm_level(smu, true, FEATURE_DPM_SOCCLK_MASK);
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

		ret = arcturus_upload_dpm_level(smu, false, FEATURE_DPM_FCLK_MASK);
		if (ret) {
			pr_err("Failed to upload boot level to lowest!\n");
			break;
		}

		ret = arcturus_upload_dpm_level(smu, true, FEATURE_DPM_FCLK_MASK);
		if (ret)
			pr_err("Failed to upload dpm max level to highest!\n");

		break;

	default:
		break;
	}

	mutex_unlock(&(smu->mutex));
	return ret;
}