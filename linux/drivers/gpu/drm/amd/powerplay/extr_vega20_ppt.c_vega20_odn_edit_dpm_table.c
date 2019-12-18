#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vega20_single_dpm_table {int count; TYPE_2__* dpm_levels; } ;
struct vega20_od8_settings {int od_gfxclk_update; TYPE_4__* od8_settings_array; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table gfx_table; struct vega20_single_dpm_table mem_table; } ;
struct TYPE_8__ {int gfxclk; } ;
struct smu_table_context {TYPE_3__ boot_values; scalar_t__ overdrive_table; } ;
struct smu_dpm_context {int /*<<< orphan*/  dpm_level; struct vega20_dpm_table* dpm_context; } ;
struct smu_context {int /*<<< orphan*/  mutex; struct smu_table_context smu_table; scalar_t__ od_settings; struct smu_dpm_context smu_dpm; } ;
struct pp_clock_levels_with_latency {TYPE_1__* data; } ;
typedef  int int32_t ;
typedef  enum PP_OD_DPM_TABLE_COMMAND { ____Placeholder_PP_OD_DPM_TABLE_COMMAND } PP_OD_DPM_TABLE_COMMAND ;
struct TYPE_10__ {int GfxclkFmin; int GfxclkFmax; int UclkFmax; int GfxclkFreq1; int GfxclkVolt1; int GfxclkFreq2; int GfxclkVolt2; int GfxclkFreq3; int GfxclkVolt3; } ;
struct TYPE_9__ {int min_value; int max_value; int /*<<< orphan*/  feature_id; } ;
struct TYPE_7__ {int value; } ;
struct TYPE_6__ {int clocks_in_khz; } ;
typedef  TYPE_5__ OverDriveTable_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_PP_TASK_READJUST_POWER_STATE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t OD8_SETTING_GFXCLK_FMAX ; 
 size_t OD8_SETTING_GFXCLK_FMIN ; 
 size_t OD8_SETTING_GFXCLK_FREQ1 ; 
 size_t OD8_SETTING_GFXCLK_FREQ2 ; 
 size_t OD8_SETTING_GFXCLK_FREQ3 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE1 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE2 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE3 ; 
 size_t OD8_SETTING_UCLK_FMAX ; 
 int /*<<< orphan*/  PPCLK_GFXCLK ; 
#define  PP_OD_COMMIT_DPM_TABLE 132 
#define  PP_OD_EDIT_MCLK_VDDC_TABLE 131 
#define  PP_OD_EDIT_SCLK_VDDC_TABLE 130 
#define  PP_OD_EDIT_VDDC_CURVE 129 
#define  PP_OD_RESTORE_DEFAULT_TABLE 128 
 int /*<<< orphan*/  SMU_FEATURE_DPM_GFXCLK_BIT ; 
 int /*<<< orphan*/  SMU_TABLE_OVERDRIVE ; 
 int VOLTAGE_SCALE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  smu_feature_is_enabled (struct smu_context*,int /*<<< orphan*/ ) ; 
 int smu_handle_task (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smu_update_table (struct smu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int vega20_get_clk_table (struct smu_context*,struct pp_clock_levels_with_latency*,struct vega20_single_dpm_table*) ; 
 int vega20_set_single_dpm_table (struct smu_context*,struct vega20_single_dpm_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega20_odn_edit_dpm_table(struct smu_context *smu,
				     enum PP_OD_DPM_TABLE_COMMAND type,
				     long *input, uint32_t size)
{
	struct smu_table_context *table_context = &smu->smu_table;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)(table_context->overdrive_table);
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	struct vega20_dpm_table *dpm_table = NULL;
	struct vega20_single_dpm_table *single_dpm_table;
	struct vega20_od8_settings *od8_settings =
		(struct vega20_od8_settings *)smu->od_settings;
	struct pp_clock_levels_with_latency clocks;
	int32_t input_index, input_clk, input_vol, i;
	int od8_id;
	int ret = 0;

	dpm_table = smu_dpm->dpm_context;

	if (!input) {
		pr_warn("NULL user input for clock and voltage\n");
		return -EINVAL;
	}

	switch (type) {
	case PP_OD_EDIT_SCLK_VDDC_TABLE:
		if (!(od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id)) {
			pr_info("Sclk min/max frequency overdrive not supported\n");
			return -EOPNOTSUPP;
		}

		for (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				pr_info("invalid number of input parameters %d\n", size);
				return -EINVAL;
			}

			input_index = input[i];
			input_clk = input[i + 1];

			if (input_index != 0 && input_index != 1) {
				pr_info("Invalid index %d\n", input_index);
				pr_info("Support min/max sclk frequency settingonly which index by 0/1\n");
				return -EINVAL;
			}

			if (input_clk < od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].min_value ||
			    input_clk > od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].max_value) {
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].max_value);
				return -EINVAL;
			}

			if (input_index == 0 && od_table->GfxclkFmin != input_clk) {
				od_table->GfxclkFmin = input_clk;
				od8_settings->od_gfxclk_update = true;
			} else if (input_index == 1 && od_table->GfxclkFmax != input_clk) {
				od_table->GfxclkFmax = input_clk;
				od8_settings->od_gfxclk_update = true;
			}
		}

		break;

	case PP_OD_EDIT_MCLK_VDDC_TABLE:
		if (!od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id) {
			pr_info("Mclk max frequency overdrive not supported\n");
			return -EOPNOTSUPP;
		}

		single_dpm_table = &(dpm_table->mem_table);
		ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
		if (ret) {
			pr_err("Attempt to get memory clk levels Failed!");
			return ret;
		}

		for (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				pr_info("invalid number of input parameters %d\n",
					 size);
				return -EINVAL;
			}

			input_index = input[i];
			input_clk = input[i + 1];

			if (input_index != 1) {
				pr_info("Invalid index %d\n", input_index);
				pr_info("Support max Mclk frequency setting only which index by 1\n");
				return -EINVAL;
			}

			if (input_clk < clocks.data[0].clocks_in_khz / 1000 ||
			    input_clk > od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].max_value) {
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					clocks.data[0].clocks_in_khz / 1000,
					od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].max_value);
				return -EINVAL;
			}

			if (input_index == 1 && od_table->UclkFmax != input_clk) {
				od8_settings->od_gfxclk_update = true;
				od_table->UclkFmax = input_clk;
			}
		}

		break;

	case PP_OD_EDIT_VDDC_CURVE:
		if (!(od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		      od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id)) {
			pr_info("Voltage curve calibrate not supported\n");
			return -EOPNOTSUPP;
		}

		for (i = 0; i < size; i += 3) {
			if (i + 3 > size) {
				pr_info("invalid number of input parameters %d\n",
					size);
				return -EINVAL;
			}

			input_index = input[i];
			input_clk = input[i + 1];
			input_vol = input[i + 2];

			if (input_index > 2) {
				pr_info("Setting for point %d is not supported\n",
					input_index + 1);
				pr_info("Three supported points index by 0, 1, 2\n");
				return -EINVAL;
			}

			od8_id = OD8_SETTING_GFXCLK_FREQ1 + 2 * input_index;
			if (input_clk < od8_settings->od8_settings_array[od8_id].min_value ||
			    input_clk > od8_settings->od8_settings_array[od8_id].max_value) {
				pr_info("clock freq %d is not within allowed range [%d - %d]\n",
					input_clk,
					od8_settings->od8_settings_array[od8_id].min_value,
					od8_settings->od8_settings_array[od8_id].max_value);
				return -EINVAL;
			}

			od8_id = OD8_SETTING_GFXCLK_VOLTAGE1 + 2 * input_index;
			if (input_vol < od8_settings->od8_settings_array[od8_id].min_value ||
			    input_vol > od8_settings->od8_settings_array[od8_id].max_value) {
				pr_info("clock voltage %d is not within allowed range [%d- %d]\n",
					input_vol,
					od8_settings->od8_settings_array[od8_id].min_value,
					od8_settings->od8_settings_array[od8_id].max_value);
				return -EINVAL;
			}

			switch (input_index) {
			case 0:
				od_table->GfxclkFreq1 = input_clk;
				od_table->GfxclkVolt1 = input_vol * VOLTAGE_SCALE;
				break;
			case 1:
				od_table->GfxclkFreq2 = input_clk;
				od_table->GfxclkVolt2 = input_vol * VOLTAGE_SCALE;
				break;
			case 2:
				od_table->GfxclkFreq3 = input_clk;
				od_table->GfxclkVolt3 = input_vol * VOLTAGE_SCALE;
				break;
			}
		}

		break;

	case PP_OD_RESTORE_DEFAULT_TABLE:
		ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0, table_context->overdrive_table, false);
		if (ret) {
			pr_err("Failed to export over drive table!\n");
			return ret;
		}

		break;

	case PP_OD_COMMIT_DPM_TABLE:
		ret = smu_update_table(smu, SMU_TABLE_OVERDRIVE, 0, table_context->overdrive_table, true);
		if (ret) {
			pr_err("Failed to import over drive table!\n");
			return ret;
		}

		/* retrieve updated gfxclk table */
		if (od8_settings->od_gfxclk_update) {
			od8_settings->od_gfxclk_update = false;
			single_dpm_table = &(dpm_table->gfx_table);

			if (smu_feature_is_enabled(smu, SMU_FEATURE_DPM_GFXCLK_BIT)) {
				ret = vega20_set_single_dpm_table(smu, single_dpm_table,
								  PPCLK_GFXCLK);
				if (ret) {
					pr_err("[Setoverdrive] failed to refresh dpm table!\n");
					return ret;
				}
			} else {
				single_dpm_table->count = 1;
				single_dpm_table->dpm_levels[0].value = smu->smu_table.boot_values.gfxclk / 100;
			}
		}

		break;

	default:
		return -EINVAL;
	}

	if (type == PP_OD_COMMIT_DPM_TABLE) {
		mutex_lock(&(smu->mutex));
		ret = smu_handle_task(smu, smu_dpm->dpm_level,
				      AMD_PP_TASK_READJUST_POWER_STATE);
		mutex_unlock(&(smu->mutex));
	}

	return ret;
}