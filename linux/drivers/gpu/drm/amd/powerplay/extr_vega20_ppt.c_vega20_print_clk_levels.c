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
struct vega20_single_dpm_table {int count; TYPE_1__* dpm_levels; } ;
struct vega20_od8_settings {TYPE_3__* od8_settings_array; } ;
struct vega20_dpm_table {struct vega20_single_dpm_table mem_table; struct vega20_single_dpm_table dcef_table; struct vega20_single_dpm_table fclk_table; struct vega20_single_dpm_table soc_table; struct vega20_single_dpm_table gfx_table; } ;
struct smu_table_context {scalar_t__ driver_pptable; scalar_t__ overdrive_table; } ;
struct smu_dpm_context {struct vega20_dpm_table* dpm_context; } ;
struct smu_context {scalar_t__ od_settings; struct smu_dpm_context smu_dpm; struct smu_table_context smu_table; struct amdgpu_device* adev; } ;
struct pp_clock_levels_with_latency {int num_levels; TYPE_2__* data; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum smu_clk_type { ____Placeholder_smu_clk_type } smu_clk_type ;
struct TYPE_10__ {int GfxclkFmin; int GfxclkFmax; int UclkFmax; int GfxclkFreq1; int GfxclkVolt1; int GfxclkFreq2; int GfxclkVolt2; int GfxclkFreq3; int GfxclkVolt3; } ;
struct TYPE_9__ {int* PcieGenSpeed; int* PcieLaneCount; int* LclkFreq; } ;
struct TYPE_8__ {int min_value; int max_value; int /*<<< orphan*/  feature_id; } ;
struct TYPE_7__ {int clocks_in_khz; } ;
struct TYPE_6__ {int value; } ;
typedef  TYPE_4__ PPTable_t ;
typedef  TYPE_5__ OverDriveTable_t ;

/* Variables and functions */
 int NUM_LINK_LEVELS ; 
 size_t OD8_SETTING_GFXCLK_FMAX ; 
 size_t OD8_SETTING_GFXCLK_FMIN ; 
 size_t OD8_SETTING_GFXCLK_FREQ1 ; 
 size_t OD8_SETTING_GFXCLK_FREQ2 ; 
 size_t OD8_SETTING_GFXCLK_FREQ3 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE1 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE2 ; 
 size_t OD8_SETTING_GFXCLK_VOLTAGE3 ; 
 size_t OD8_SETTING_UCLK_FMAX ; 
 int PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK ; 
 int PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT ; 
 int PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK ; 
 int PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT ; 
 int RREG32_PCIE (int /*<<< orphan*/ ) ; 
#define  SMU_DCEFCLK 137 
#define  SMU_FCLK 136 
 int const SMU_GFXCLK ; 
#define  SMU_MCLK 135 
#define  SMU_OD_MCLK 134 
#define  SMU_OD_RANGE 133 
#define  SMU_OD_SCLK 132 
#define  SMU_OD_VDDC_CURVE 131 
#define  SMU_PCIE 130 
#define  SMU_SCLK 129 
#define  SMU_SOCCLK 128 
 int const SMU_UCLK ; 
 int VOLTAGE_SCALE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smnPCIE_LC_LINK_WIDTH_CNTL ; 
 int /*<<< orphan*/  smnPCIE_LC_SPEED_CNTL ; 
 int smu_get_current_clk_freq (struct smu_context*,int const,int*) ; 
 int sprintf (char*,char*,...) ; 
 int vega20_get_clk_table (struct smu_context*,struct pp_clock_levels_with_latency*,struct vega20_single_dpm_table*) ; 

__attribute__((used)) static int vega20_print_clk_levels(struct smu_context *smu,
			enum smu_clk_type type, char *buf)
{
	int i, now, size = 0;
	int ret = 0;
	uint32_t gen_speed, lane_width;
	struct amdgpu_device *adev = smu->adev;
	struct pp_clock_levels_with_latency clocks;
	struct vega20_single_dpm_table *single_dpm_table;
	struct smu_table_context *table_context = &smu->smu_table;
	struct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	struct vega20_dpm_table *dpm_table = NULL;
	struct vega20_od8_settings *od8_settings =
		(struct vega20_od8_settings *)smu->od_settings;
	OverDriveTable_t *od_table =
		(OverDriveTable_t *)(table_context->overdrive_table);
	PPTable_t *pptable = (PPTable_t *)table_context->driver_pptable;

	dpm_table = smu_dpm->dpm_context;

	switch (type) {
	case SMU_SCLK:
		ret = smu_get_current_clk_freq(smu, SMU_GFXCLK, &now);
		if (ret) {
			pr_err("Attempt to get current gfx clk Failed!");
			return ret;
		}

		single_dpm_table = &(dpm_table->gfx_table);
		ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
		if (ret) {
			pr_err("Attempt to get gfx clk levels Failed!");
			return ret;
		}

		for (i = 0; i < clocks.num_levels; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n", i,
					clocks.data[i].clocks_in_khz / 1000,
					(clocks.data[i].clocks_in_khz == now * 10)
					? "*" : "");
		break;

	case SMU_MCLK:
		ret = smu_get_current_clk_freq(smu, SMU_UCLK, &now);
		if (ret) {
			pr_err("Attempt to get current mclk Failed!");
			return ret;
		}

		single_dpm_table = &(dpm_table->mem_table);
		ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
		if (ret) {
			pr_err("Attempt to get memory clk levels Failed!");
			return ret;
		}

		for (i = 0; i < clocks.num_levels; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
				i, clocks.data[i].clocks_in_khz / 1000,
				(clocks.data[i].clocks_in_khz == now * 10)
				? "*" : "");
		break;

	case SMU_SOCCLK:
		ret = smu_get_current_clk_freq(smu, SMU_SOCCLK, &now);
		if (ret) {
			pr_err("Attempt to get current socclk Failed!");
			return ret;
		}

		single_dpm_table = &(dpm_table->soc_table);
		ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
		if (ret) {
			pr_err("Attempt to get socclk levels Failed!");
			return ret;
		}

		for (i = 0; i < clocks.num_levels; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
				i, clocks.data[i].clocks_in_khz / 1000,
				(clocks.data[i].clocks_in_khz == now * 10)
				? "*" : "");
		break;

	case SMU_FCLK:
		ret = smu_get_current_clk_freq(smu, SMU_FCLK, &now);
		if (ret) {
			pr_err("Attempt to get current fclk Failed!");
			return ret;
		}

		single_dpm_table = &(dpm_table->fclk_table);
		for (i = 0; i < single_dpm_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
				i, single_dpm_table->dpm_levels[i].value,
				(single_dpm_table->dpm_levels[i].value == now / 100)
				? "*" : "");
		break;

	case SMU_DCEFCLK:
		ret = smu_get_current_clk_freq(smu, SMU_DCEFCLK, &now);
		if (ret) {
			pr_err("Attempt to get current dcefclk Failed!");
			return ret;
		}

		single_dpm_table = &(dpm_table->dcef_table);
		ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
		if (ret) {
			pr_err("Attempt to get dcefclk levels Failed!");
			return ret;
		}

		for (i = 0; i < clocks.num_levels; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
				i, clocks.data[i].clocks_in_khz / 1000,
				(clocks.data[i].clocks_in_khz == now * 10) ? "*" : "");
		break;

	case SMU_PCIE:
		gen_speed = (RREG32_PCIE(smnPCIE_LC_SPEED_CNTL) &
			     PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE_MASK)
			>> PSWUSP0_PCIE_LC_SPEED_CNTL__LC_CURRENT_DATA_RATE__SHIFT;
		lane_width = (RREG32_PCIE(smnPCIE_LC_LINK_WIDTH_CNTL) &
			      PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD_MASK)
			>> PCIE_LC_LINK_WIDTH_CNTL__LC_LINK_WIDTH_RD__SHIFT;
		for (i = 0; i < NUM_LINK_LEVELS; i++)
			size += sprintf(buf + size, "%d: %s %s %dMhz %s\n", i,
					(pptable->PcieGenSpeed[i] == 0) ? "2.5GT/s," :
					(pptable->PcieGenSpeed[i] == 1) ? "5.0GT/s," :
					(pptable->PcieGenSpeed[i] == 2) ? "8.0GT/s," :
					(pptable->PcieGenSpeed[i] == 3) ? "16.0GT/s," : "",
					(pptable->PcieLaneCount[i] == 1) ? "x1" :
					(pptable->PcieLaneCount[i] == 2) ? "x2" :
					(pptable->PcieLaneCount[i] == 3) ? "x4" :
					(pptable->PcieLaneCount[i] == 4) ? "x8" :
					(pptable->PcieLaneCount[i] == 5) ? "x12" :
					(pptable->PcieLaneCount[i] == 6) ? "x16" : "",
					pptable->LclkFreq[i],
					(gen_speed == pptable->PcieGenSpeed[i]) &&
					(lane_width == pptable->PcieLaneCount[i]) ?
					"*" : "");
		break;

	case SMU_OD_SCLK:
		if (od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id) {
			size = sprintf(buf, "%s:\n", "OD_SCLK");
			size += sprintf(buf + size, "0: %10uMhz\n",
					od_table->GfxclkFmin);
			size += sprintf(buf + size, "1: %10uMhz\n",
					od_table->GfxclkFmax);
		}

		break;

	case SMU_OD_MCLK:
		if (od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id) {
			size = sprintf(buf, "%s:\n", "OD_MCLK");
			size += sprintf(buf + size, "1: %10uMhz\n",
					 od_table->UclkFmax);
		}

		break;

	case SMU_OD_VDDC_CURVE:
		if (od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id) {
			size = sprintf(buf, "%s:\n", "OD_VDDC_CURVE");
			size += sprintf(buf + size, "0: %10uMhz %10dmV\n",
					od_table->GfxclkFreq1,
					od_table->GfxclkVolt1 / VOLTAGE_SCALE);
			size += sprintf(buf + size, "1: %10uMhz %10dmV\n",
					od_table->GfxclkFreq2,
					od_table->GfxclkVolt2 / VOLTAGE_SCALE);
			size += sprintf(buf + size, "2: %10uMhz %10dmV\n",
					od_table->GfxclkFreq3,
					od_table->GfxclkVolt3 / VOLTAGE_SCALE);
		}

		break;

	case SMU_OD_RANGE:
		size = sprintf(buf, "%s:\n", "OD_RANGE");

		if (od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].feature_id) {
			size += sprintf(buf + size, "SCLK: %7uMhz %10uMhz\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMIN].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FMAX].max_value);
		}

		if (od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].feature_id) {
			single_dpm_table = &(dpm_table->mem_table);
			ret = vega20_get_clk_table(smu, &clocks, single_dpm_table);
			if (ret) {
				pr_err("Attempt to get memory clk levels Failed!");
				return ret;
			}

			size += sprintf(buf + size, "MCLK: %7uMhz %10uMhz\n",
					clocks.data[0].clocks_in_khz / 1000,
					od8_settings->od8_settings_array[OD8_SETTING_UCLK_FMAX].max_value);
		}

		if (od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].feature_id &&
		    od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].feature_id) {
			size += sprintf(buf + size, "VDDC_CURVE_SCLK[0]: %7uMhz %10uMhz\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ1].max_value);
			size += sprintf(buf + size, "VDDC_CURVE_VOLT[0]: %7dmV %11dmV\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE1].max_value);
			size += sprintf(buf + size, "VDDC_CURVE_SCLK[1]: %7uMhz %10uMhz\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ2].max_value);
			size += sprintf(buf + size, "VDDC_CURVE_VOLT[1]: %7dmV %11dmV\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE2].max_value);
			size += sprintf(buf + size, "VDDC_CURVE_SCLK[2]: %7uMhz %10uMhz\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_FREQ3].max_value);
			size += sprintf(buf + size, "VDDC_CURVE_VOLT[2]: %7dmV %11dmV\n",
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].min_value,
					od8_settings->od8_settings_array[OD8_SETTING_GFXCLK_VOLTAGE3].max_value);
		}

		break;

	default:
		break;
	}
	return size;
}