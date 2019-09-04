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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct smu7_power_state {TYPE_1__* performance_levels; } ;
struct TYPE_5__ {scalar_t__ pcie_lane_bootup_value; int /*<<< orphan*/  pcie_gen_bootup_value; void* sclk_bootup_value; void* mclk_bootup_value; void* vddci_bootup_value; void* vddc_bootup_value; void* mvdd_bootup_value; } ;
struct smu7_hwmgr {TYPE_2__ vbios_boot_state; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;
struct pp_hw_power_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  usBootUpVDDCIVoltage; int /*<<< orphan*/  usBootUpVDDCVoltage; int /*<<< orphan*/  usBootUpMVDDCVoltage; int /*<<< orphan*/  ulDefaultMemoryClock; int /*<<< orphan*/  ulDefaultEngineClock; } ;
struct TYPE_4__ {scalar_t__ pcie_lane; int /*<<< orphan*/  pcie_gen; void* engine_clock; void* memory_clock; } ;
typedef  TYPE_3__ ATOM_FIRMWARE_INFO_V2_2 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ smu7_get_current_pcie_lane_number (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smu7_get_current_pcie_speed (struct pp_hwmgr*) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smu7_dpm_patch_boot_state(struct pp_hwmgr *hwmgr,
					struct pp_hw_power_state *hw_ps)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	struct smu7_power_state *ps = (struct smu7_power_state *)hw_ps;
	ATOM_FIRMWARE_INFO_V2_2 *fw_info;
	uint16_t size;
	uint8_t frev, crev;
	int index = GetIndexIntoMasterTable(DATA, FirmwareInfo);

	/* First retrieve the Boot clocks and VDDC from the firmware info table.
	 * We assume here that fw_info is unchanged if this call fails.
	 */
	fw_info = (ATOM_FIRMWARE_INFO_V2_2 *)smu_atom_get_data_table(hwmgr->adev, index,
			&size, &frev, &crev);
	if (!fw_info)
		/* During a test, there is no firmware info table. */
		return 0;

	/* Patch the state. */
	data->vbios_boot_state.sclk_bootup_value =
			le32_to_cpu(fw_info->ulDefaultEngineClock);
	data->vbios_boot_state.mclk_bootup_value =
			le32_to_cpu(fw_info->ulDefaultMemoryClock);
	data->vbios_boot_state.mvdd_bootup_value =
			le16_to_cpu(fw_info->usBootUpMVDDCVoltage);
	data->vbios_boot_state.vddc_bootup_value =
			le16_to_cpu(fw_info->usBootUpVDDCVoltage);
	data->vbios_boot_state.vddci_bootup_value =
			le16_to_cpu(fw_info->usBootUpVDDCIVoltage);
	data->vbios_boot_state.pcie_gen_bootup_value =
			smu7_get_current_pcie_speed(hwmgr);

	data->vbios_boot_state.pcie_lane_bootup_value =
			(uint16_t)smu7_get_current_pcie_lane_number(hwmgr);

	/* set boot power state */
	ps->performance_levels[0].memory_clock = data->vbios_boot_state.mclk_bootup_value;
	ps->performance_levels[0].engine_clock = data->vbios_boot_state.sclk_bootup_value;
	ps->performance_levels[0].pcie_gen = data->vbios_boot_state.pcie_gen_bootup_value;
	ps->performance_levels[0].pcie_lane = data->vbios_boot_state.pcie_lane_bootup_value;

	return 0;
}