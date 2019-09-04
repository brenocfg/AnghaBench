#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct pp_atomfwctrl_bios_boot_up_values {int dummy; } ;
struct atom_firmware_info_v3_2 {int dummy; } ;
struct atom_firmware_info_v3_1 {int dummy; } ;
struct atom_common_table_header {int format_revision; int content_revision; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GetIndexIntoMasterDataTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmwareinfo ; 
 int /*<<< orphan*/  pp_atomfwctrl_copy_vbios_bootup_values_3_1 (struct pp_hwmgr*,struct pp_atomfwctrl_bios_boot_up_values*,struct atom_firmware_info_v3_1*) ; 
 int /*<<< orphan*/  pp_atomfwctrl_copy_vbios_bootup_values_3_2 (struct pp_hwmgr*,struct pp_atomfwctrl_bios_boot_up_values*,struct atom_firmware_info_v3_2*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pp_atomfwctrl_get_vbios_bootup_values(struct pp_hwmgr *hwmgr,
			struct pp_atomfwctrl_bios_boot_up_values *boot_values)
{
	struct atom_firmware_info_v3_2 *fwinfo_3_2;
	struct atom_firmware_info_v3_1 *fwinfo_3_1;
	struct atom_common_table_header *info = NULL;
	uint16_t ix;

	ix = GetIndexIntoMasterDataTable(firmwareinfo);
	info = (struct atom_common_table_header *)
		smu_atom_get_data_table(hwmgr->adev,
				ix, NULL, NULL, NULL);

	if (!info) {
		pr_info("Error retrieving BIOS firmwareinfo!");
		return -EINVAL;
	}

	if ((info->format_revision == 3) && (info->content_revision == 2)) {
		fwinfo_3_2 = (struct atom_firmware_info_v3_2 *)info;
		pp_atomfwctrl_copy_vbios_bootup_values_3_2(hwmgr,
				boot_values, fwinfo_3_2);
	} else if ((info->format_revision == 3) && (info->content_revision == 1)) {
		fwinfo_3_1 = (struct atom_firmware_info_v3_1 *)info;
		pp_atomfwctrl_copy_vbios_bootup_values_3_1(hwmgr,
				boot_values, fwinfo_3_1);
	} else {
		pr_info("Fw info table revision does not match!");
		return -EINVAL;
	}

	return 0;
}