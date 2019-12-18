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
struct pqi_scsi_dev {int /*<<< orphan*/  bay; int /*<<< orphan*/  phys_connector; int /*<<< orphan*/  box; int /*<<< orphan*/  path_map; int /*<<< orphan*/  active_path_index; int /*<<< orphan*/  device_type; int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  phy_connected_dev_type; int /*<<< orphan*/  phys_box_on_bus; int /*<<< orphan*/  box_index; } ;
struct pqi_ctrl_info {int dummy; } ;
struct bmic_identify_physical_device {int /*<<< orphan*/  phys_bay_in_box; int /*<<< orphan*/  alternate_paths_phys_connector; int /*<<< orphan*/  alternate_paths_phys_box_on_port; int /*<<< orphan*/  redundant_path_present_map; int /*<<< orphan*/  active_path_number; int /*<<< orphan*/  device_type; int /*<<< orphan*/  current_queue_depth_limit; int /*<<< orphan*/ * phy_connected_dev_type; int /*<<< orphan*/  phys_box_on_bus; int /*<<< orphan*/  box_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQI_PHYSICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bmic_identify_physical_device*,int /*<<< orphan*/ ,int) ; 
 int pqi_identify_physical_device (struct pqi_ctrl_info*,struct pqi_scsi_dev*,struct bmic_identify_physical_device*,int) ; 

__attribute__((used)) static void pqi_get_physical_disk_info(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device,
	struct bmic_identify_physical_device *id_phys)
{
	int rc;

	memset(id_phys, 0, sizeof(*id_phys));

	rc = pqi_identify_physical_device(ctrl_info, device,
		id_phys, sizeof(*id_phys));
	if (rc) {
		device->queue_depth = PQI_PHYSICAL_DISK_DEFAULT_MAX_QUEUE_DEPTH;
		return;
	}
	device->box_index = id_phys->box_index;
	device->phys_box_on_bus = id_phys->phys_box_on_bus;
	device->phy_connected_dev_type = id_phys->phy_connected_dev_type[0];
	device->queue_depth =
		get_unaligned_le16(&id_phys->current_queue_depth_limit);
	device->device_type = id_phys->device_type;
	device->active_path_index = id_phys->active_path_number;
	device->path_map = id_phys->redundant_path_present_map;
	memcpy(&device->box,
		&id_phys->alternate_paths_phys_box_on_port,
		sizeof(device->box));
	memcpy(&device->phys_connector,
		&id_phys->alternate_paths_phys_connector,
		sizeof(device->phys_connector));
	device->bay = id_phys->phys_bay_in_box;
}