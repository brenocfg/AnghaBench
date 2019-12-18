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
struct hpsa_scsi_dev_t {int hba_ioaccel_enabled; int /*<<< orphan*/  bay; int /*<<< orphan*/  phys_connector; int /*<<< orphan*/  box; int /*<<< orphan*/  path_map; int /*<<< orphan*/  active_path_index; scalar_t__ ioaccel_handle; } ;
struct ext_report_lun_entry {int device_flags; } ;
struct bmic_identify_physical_device {int /*<<< orphan*/  phys_bay_in_box; int /*<<< orphan*/  alternate_paths_phys_connector; int /*<<< orphan*/  alternate_paths_phys_box_on_port; int /*<<< orphan*/  redundant_path_present_map; int /*<<< orphan*/  active_path_number; } ;
struct ReportExtendedLUNdata {struct ext_report_lun_entry* LUN; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hpsa_get_path_info(struct hpsa_scsi_dev_t *this_device,
	struct ReportExtendedLUNdata *rlep, int rle_index,
	struct bmic_identify_physical_device *id_phys)
{
	struct ext_report_lun_entry *rle = &rlep->LUN[rle_index];

	if ((rle->device_flags & 0x08) && this_device->ioaccel_handle)
		this_device->hba_ioaccel_enabled = 1;

	memcpy(&this_device->active_path_index,
		&id_phys->active_path_number,
		sizeof(this_device->active_path_index));
	memcpy(&this_device->path_map,
		&id_phys->redundant_path_present_map,
		sizeof(this_device->path_map));
	memcpy(&this_device->box,
		&id_phys->alternate_paths_phys_box_on_port,
		sizeof(this_device->box));
	memcpy(&this_device->phys_connector,
		&id_phys->alternate_paths_phys_connector,
		sizeof(this_device->phys_connector));
	memcpy(&this_device->bay,
		&id_phys->phys_bay_in_box,
		sizeof(this_device->bay));
}