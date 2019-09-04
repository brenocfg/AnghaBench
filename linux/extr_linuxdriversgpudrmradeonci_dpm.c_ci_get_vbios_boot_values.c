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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct radeon_mode_info {TYPE_2__* atom_context; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct ci_vbios_boot_state {void* mclk_bootup_value; void* sclk_bootup_value; int /*<<< orphan*/  pcie_lane_bootup_value; int /*<<< orphan*/  pcie_gen_bootup_value; void* vddci_bootup_value; void* vddc_bootup_value; void* mvdd_bootup_value; } ;
struct TYPE_4__ {scalar_t__ bios; } ;
struct TYPE_3__ {int /*<<< orphan*/  ulDefaultMemoryClock; int /*<<< orphan*/  ulDefaultEngineClock; int /*<<< orphan*/  usBootUpVDDCIVoltage; int /*<<< orphan*/  usBootUpVDDCVoltage; int /*<<< orphan*/  usBootUpMVDDCVoltage; } ;
typedef  TYPE_1__ ATOM_FIRMWARE_INFO_V2_2 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  FirmwareInfo ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_data_header (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ci_get_current_pcie_lane_number (struct radeon_device*) ; 
 int /*<<< orphan*/  ci_get_current_pcie_speed (struct radeon_device*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_get_vbios_boot_values(struct radeon_device *rdev,
				    struct ci_vbios_boot_state *boot_state)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, FirmwareInfo);
	ATOM_FIRMWARE_INFO_V2_2 *firmware_info;
	u8 frev, crev;
	u16 data_offset;

	if (atom_parse_data_header(mode_info->atom_context, index, NULL,
				   &frev, &crev, &data_offset)) {
		firmware_info =
			(ATOM_FIRMWARE_INFO_V2_2 *)(mode_info->atom_context->bios +
						    data_offset);
		boot_state->mvdd_bootup_value = le16_to_cpu(firmware_info->usBootUpMVDDCVoltage);
		boot_state->vddc_bootup_value = le16_to_cpu(firmware_info->usBootUpVDDCVoltage);
		boot_state->vddci_bootup_value = le16_to_cpu(firmware_info->usBootUpVDDCIVoltage);
		boot_state->pcie_gen_bootup_value = ci_get_current_pcie_speed(rdev);
		boot_state->pcie_lane_bootup_value = ci_get_current_pcie_lane_number(rdev);
		boot_state->sclk_bootup_value = le32_to_cpu(firmware_info->ulDefaultEngineClock);
		boot_state->mclk_bootup_value = le32_to_cpu(firmware_info->ulDefaultMemoryClock);

		return 0;
	}
	return -EINVAL;
}