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
typedef  int u32 ;
struct pqi_scsi_dev {int bus; int target; int lun; char sas_address; char* vendor; char* model; scalar_t__ devtype; char queue_depth; scalar_t__ aio_enabled; int /*<<< orphan*/  raid_level; scalar_t__ raid_bypass_enabled; scalar_t__ raid_bypass_configured; int /*<<< orphan*/ * scsi3addr; scalar_t__ target_lun_valid; } ;
struct pqi_ctrl_info {TYPE_2__* pci_dev; TYPE_1__* scsi_host; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 int PQI_DEV_INFO_BUFFER_LENGTH ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_ZBC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* pqi_device_type (struct pqi_scsi_dev*) ; 
 scalar_t__ pqi_is_logical_device (struct pqi_scsi_dev*) ; 
 char* pqi_raid_level_to_string (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void pqi_dev_info(struct pqi_ctrl_info *ctrl_info,
	char *action, struct pqi_scsi_dev *device)
{
	ssize_t count;
	char buffer[PQI_DEV_INFO_BUFFER_LENGTH];

	count = snprintf(buffer, PQI_DEV_INFO_BUFFER_LENGTH,
		"%d:%d:", ctrl_info->scsi_host->host_no, device->bus);

	if (device->target_lun_valid)
		count += snprintf(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"%d:%d",
			device->target,
			device->lun);
	else
		count += snprintf(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"-:-");

	if (pqi_is_logical_device(device))
		count += snprintf(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			" %08x%08x",
			*((u32 *)&device->scsi3addr),
			*((u32 *)&device->scsi3addr[4]));
	else
		count += snprintf(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			" %016llx", device->sas_address);

	count += snprintf(buffer + count, PQI_DEV_INFO_BUFFER_LENGTH - count,
		" %s %.8s %.16s ",
		pqi_device_type(device),
		device->vendor,
		device->model);

	if (pqi_is_logical_device(device)) {
		if (device->devtype == TYPE_DISK)
			count += snprintf(buffer + count,
				PQI_DEV_INFO_BUFFER_LENGTH - count,
				"SSDSmartPathCap%c En%c %-12s",
				device->raid_bypass_configured ? '+' : '-',
				device->raid_bypass_enabled ? '+' : '-',
				pqi_raid_level_to_string(device->raid_level));
	} else {
		count += snprintf(buffer + count,
			PQI_DEV_INFO_BUFFER_LENGTH - count,
			"AIO%c", device->aio_enabled ? '+' : '-');
		if (device->devtype == TYPE_DISK ||
			device->devtype == TYPE_ZBC)
			count += snprintf(buffer + count,
				PQI_DEV_INFO_BUFFER_LENGTH - count,
				" qd=%-6d", device->queue_depth);
	}

	dev_info(&ctrl_info->pci_dev->dev, "%s %s\n", action, buffer);
}