#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_22__ {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; } ;
struct smu7_power_state {int dc_compatible; size_t performance_level_count; TYPE_12__* performance_levels; TYPE_5__ uvd_clks; } ;
struct TYPE_15__ {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct TYPE_14__ {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct TYPE_26__ {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct TYPE_25__ {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
struct TYPE_20__ {scalar_t__ mclk_bootup_value; scalar_t__ vddci_bootup_value; } ;
struct smu7_hwmgr {int use_pcie_performance_levels; int use_pcie_power_saving_levels; TYPE_11__ pcie_lane_power_saving; TYPE_10__ pcie_gen_power_saving; TYPE_9__ pcie_lane_performance; TYPE_8__ pcie_gen_performance; int /*<<< orphan*/  acpi_pcie_gen; TYPE_3__ vbios_boot_state; } ;
struct TYPE_24__ {int flags; int ui_label; } ;
struct TYPE_23__ {int /*<<< orphan*/  DCLK; int /*<<< orphan*/  VCLK; } ;
struct TYPE_21__ {int /*<<< orphan*/  disallowOnDC; } ;
struct TYPE_17__ {int /*<<< orphan*/  magic; } ;
struct pp_power_state {TYPE_7__ classification; TYPE_6__ uvd_clocks; TYPE_4__ validation; TYPE_13__ hardware; } ;
struct TYPE_18__ {struct phm_clock_voltage_dependency_table* vddci_dependency_on_mclk; } ;
struct pp_hwmgr {TYPE_1__ dyn_state; scalar_t__ backend; } ;
struct pp_hw_power_state {int dummy; } ;
struct phm_clock_voltage_dependency_table {int count; TYPE_2__* entries; } ;
struct TYPE_19__ {scalar_t__ clk; scalar_t__ v; } ;
struct TYPE_16__ {int /*<<< orphan*/  pcie_lane; int /*<<< orphan*/  pcie_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_VIslands_Magic ; 
 int PP_StateClassificationFlag_ACPI ; 
#define  PP_StateUILabel_Battery 129 
#define  PP_StateUILabel_Performance 128 
 int /*<<< orphan*/  memset (TYPE_13__*,int,int) ; 
 int pp_tables_get_entry (struct pp_hwmgr*,unsigned long,struct pp_power_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  smu7_get_pp_table_entry_callback_func_v0 ; 

__attribute__((used)) static int smu7_get_pp_table_entry_v0(struct pp_hwmgr *hwmgr,
		unsigned long entry_index, struct pp_power_state *state)
{
	int result;
	struct smu7_power_state *ps;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct phm_clock_voltage_dependency_table *dep_mclk_table =
			hwmgr->dyn_state.vddci_dependency_on_mclk;

	memset(&state->hardware, 0x00, sizeof(struct pp_hw_power_state));

	state->hardware.magic = PHM_VIslands_Magic;

	ps = (struct smu7_power_state *)(&state->hardware);

	result = pp_tables_get_entry(hwmgr, entry_index, state,
			smu7_get_pp_table_entry_callback_func_v0);

	/*
	 * This is the earliest time we have all the dependency table
	 * and the VBIOS boot state as
	 * PP_Tables_GetPowerPlayTableEntry retrieves the VBIOS boot
	 * state if there is only one VDDCI/MCLK level, check if it's
	 * the same as VBIOS boot state
	 */
	if (dep_mclk_table != NULL && dep_mclk_table->count == 1) {
		if (dep_mclk_table->entries[0].clk !=
				data->vbios_boot_state.mclk_bootup_value)
			pr_debug("Single MCLK entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot MCLK level");
		if (dep_mclk_table->entries[0].v !=
				data->vbios_boot_state.vddci_bootup_value)
			pr_debug("Single VDDCI entry VDDCI/MCLK dependency table "
					"does not match VBIOS boot VDDCI level");
	}

	/* set DC compatible flag if this state supports DC */
	if (!state->validation.disallowOnDC)
		ps->dc_compatible = true;

	if (state->classification.flags & PP_StateClassificationFlag_ACPI)
		data->acpi_pcie_gen = ps->performance_levels[0].pcie_gen;

	ps->uvd_clks.vclk = state->uvd_clocks.VCLK;
	ps->uvd_clks.dclk = state->uvd_clocks.DCLK;

	if (!result) {
		uint32_t i;

		switch (state->classification.ui_label) {
		case PP_StateUILabel_Performance:
			data->use_pcie_performance_levels = true;

			for (i = 0; i < ps->performance_level_count; i++) {
				if (data->pcie_gen_performance.max <
						ps->performance_levels[i].pcie_gen)
					data->pcie_gen_performance.max =
							ps->performance_levels[i].pcie_gen;

				if (data->pcie_gen_performance.min >
						ps->performance_levels[i].pcie_gen)
					data->pcie_gen_performance.min =
							ps->performance_levels[i].pcie_gen;

				if (data->pcie_lane_performance.max <
						ps->performance_levels[i].pcie_lane)
					data->pcie_lane_performance.max =
							ps->performance_levels[i].pcie_lane;

				if (data->pcie_lane_performance.min >
						ps->performance_levels[i].pcie_lane)
					data->pcie_lane_performance.min =
							ps->performance_levels[i].pcie_lane;
			}
			break;
		case PP_StateUILabel_Battery:
			data->use_pcie_power_saving_levels = true;

			for (i = 0; i < ps->performance_level_count; i++) {
				if (data->pcie_gen_power_saving.max <
						ps->performance_levels[i].pcie_gen)
					data->pcie_gen_power_saving.max =
							ps->performance_levels[i].pcie_gen;

				if (data->pcie_gen_power_saving.min >
						ps->performance_levels[i].pcie_gen)
					data->pcie_gen_power_saving.min =
							ps->performance_levels[i].pcie_gen;

				if (data->pcie_lane_power_saving.max <
						ps->performance_levels[i].pcie_lane)
					data->pcie_lane_power_saving.max =
							ps->performance_levels[i].pcie_lane;

				if (data->pcie_lane_power_saving.min >
						ps->performance_levels[i].pcie_lane)
					data->pcie_lane_power_saving.min =
							ps->performance_levels[i].pcie_lane;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}