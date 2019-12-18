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
typedef  int u8 ;
struct pqi_scsi_dev {int devtype; int volume_offline; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; int /*<<< orphan*/  unique_id; int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  volume_status; int /*<<< orphan*/  raid_level; scalar_t__ is_external_raid_device; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; scalar_t__ is_expander_smp_device; } ;
struct pqi_ctrl_info {TYPE_2__* scsi_host; TYPE_1__* pci_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_LV_OK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PQI_CMD_STATUS_ABORTED ; 
 unsigned int PQI_INQUIRY_PAGE0_RETRIES ; 
 int /*<<< orphan*/  SA_RAID_UNKNOWN ; 
 int TYPE_DISK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ pqi_get_device_id (struct pqi_ctrl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pqi_get_raid_bypass_status (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_get_raid_level (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int /*<<< orphan*/  pqi_get_volume_status (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 scalar_t__ pqi_is_logical_device (struct pqi_scsi_dev*) ; 
 int pqi_scsi_inquiry (struct pqi_ctrl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  scsi_sanitize_inquiry_string (int*,int) ; 

__attribute__((used)) static int pqi_get_device_info(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;
	u8 *buffer;
	unsigned int retries;

	if (device->is_expander_smp_device)
		return 0;

	buffer = kmalloc(64, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* Send an inquiry to the device to see what it is. */
	for (retries = 0;;) {
		rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr, 0,
			buffer, 64);
		if (rc == 0)
			break;
		if (pqi_is_logical_device(device) ||
			rc != PQI_CMD_STATUS_ABORTED ||
			++retries > PQI_INQUIRY_PAGE0_RETRIES)
			goto out;
	}

	scsi_sanitize_inquiry_string(&buffer[8], 8);
	scsi_sanitize_inquiry_string(&buffer[16], 16);

	device->devtype = buffer[0] & 0x1f;
	memcpy(device->vendor, &buffer[8], sizeof(device->vendor));
	memcpy(device->model, &buffer[16], sizeof(device->model));

	if (pqi_is_logical_device(device) && device->devtype == TYPE_DISK) {
		if (device->is_external_raid_device) {
			device->raid_level = SA_RAID_UNKNOWN;
			device->volume_status = CISS_LV_OK;
			device->volume_offline = false;
		} else {
			pqi_get_raid_level(ctrl_info, device);
			pqi_get_raid_bypass_status(ctrl_info, device);
			pqi_get_volume_status(ctrl_info, device);
		}
	}

	if (pqi_get_device_id(ctrl_info, device->scsi3addr,
		device->unique_id, sizeof(device->unique_id)) < 0)
		dev_warn(&ctrl_info->pci_dev->dev,
			"Can't get device id for scsi %d:%d:%d:%d\n",
			ctrl_info->scsi_host->host_no,
			device->bus, device->target,
			device->lun);

out:
	kfree(buffer);

	return rc;
}