#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct scsi_device {struct pqi_scsi_dev* hostdata; int /*<<< orphan*/  host; } ;
struct pqi_scsi_dev {int bay; int active_path_index; int path_map; scalar_t__ devtype; int* box; int /*<<< orphan*/ * phys_connector; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  scsi_device_list_lock; TYPE_1__* scsi_host; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phys_connector ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENODEV ; 
 int MAX_PATHS ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_RAID ; 
 scalar_t__ TYPE_ZBC ; 
 int /*<<< orphan*/  memcpy (unsigned char**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pqi_expose_device (struct pqi_scsi_dev*) ; 
 scalar_t__ pqi_is_logical_device (struct pqi_scsi_dev*) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  scsi_device_type (scalar_t__) ; 
 struct pqi_ctrl_info* shost_to_hba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t pqi_path_info_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct pqi_ctrl_info *ctrl_info;
	struct scsi_device *sdev;
	struct pqi_scsi_dev *device;
	unsigned long flags;
	int i;
	int output_len = 0;
	u8 box;
	u8 bay;
	u8 path_map_index = 0;
	char *active;
	unsigned char phys_connector[2];

	sdev = to_scsi_device(dev);
	ctrl_info = shost_to_hba(sdev->host);

	spin_lock_irqsave(&ctrl_info->scsi_device_list_lock, flags);

	device = sdev->hostdata;
	if (!device) {
		spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock,
			flags);
		return -ENODEV;
	}

	bay = device->bay;
	for (i = 0; i < MAX_PATHS; i++) {
		path_map_index = 1<<i;
		if (i == device->active_path_index)
			active = "Active";
		else if (device->path_map & path_map_index)
			active = "Inactive";
		else
			continue;

		output_len += scnprintf(buf + output_len,
					PAGE_SIZE - output_len,
					"[%d:%d:%d:%d] %20.20s ",
					ctrl_info->scsi_host->host_no,
					device->bus, device->target,
					device->lun,
					scsi_device_type(device->devtype));

		if (device->devtype == TYPE_RAID ||
			pqi_is_logical_device(device))
			goto end_buffer;

		memcpy(&phys_connector, &device->phys_connector[i],
			sizeof(phys_connector));
		if (phys_connector[0] < '0')
			phys_connector[0] = '0';
		if (phys_connector[1] < '0')
			phys_connector[1] = '0';

		output_len += scnprintf(buf + output_len,
					PAGE_SIZE - output_len,
					"PORT: %.2s ", phys_connector);

		box = device->box[i];
		if (box != 0 && box != 0xFF)
			output_len += scnprintf(buf + output_len,
						PAGE_SIZE - output_len,
						"BOX: %hhu ", box);

		if ((device->devtype == TYPE_DISK ||
			device->devtype == TYPE_ZBC) &&
			pqi_expose_device(device))
			output_len += scnprintf(buf + output_len,
						PAGE_SIZE - output_len,
						"BAY: %hhu ", bay);

end_buffer:
		output_len += scnprintf(buf + output_len,
					PAGE_SIZE - output_len,
					"%s\n", active);
	}

	spin_unlock_irqrestore(&ctrl_info->scsi_device_list_lock, flags);
	return output_len;
}