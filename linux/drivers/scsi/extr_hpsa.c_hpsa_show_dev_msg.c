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
struct hpsa_scsi_dev_t {int devtype; size_t raid_level; int /*<<< orphan*/  expose_device; scalar_t__ offload_to_be_enabled; scalar_t__ offload_config; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; int /*<<< orphan*/  scsi3addr; int /*<<< orphan*/  external; } ;
struct ctlr_info {TYPE_2__* scsi_host; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LABEL_SIZE ; 
 size_t PHYSICAL_DRIVE ; 
 size_t RAID_UNKNOWN ; 
#define  TYPE_DISK 134 
#define  TYPE_ENCLOSURE 133 
#define  TYPE_MEDIUM_CHANGER 132 
#define  TYPE_RAID 131 
#define  TYPE_ROM 130 
#define  TYPE_TAPE 129 
#define  TYPE_ZBC 128 
 int /*<<< orphan*/  dev_printk (char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_logical_dev_addr_mode (int /*<<< orphan*/ ) ; 
 char** raid_label ; 
 int /*<<< orphan*/  scsi_device_type (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static void hpsa_show_dev_msg(const char *level, struct ctlr_info *h,
	struct hpsa_scsi_dev_t *dev, char *description)
{
#define LABEL_SIZE 25
	char label[LABEL_SIZE];

	if (h == NULL || h->pdev == NULL || h->scsi_host == NULL)
		return;

	switch (dev->devtype) {
	case TYPE_RAID:
		snprintf(label, LABEL_SIZE, "controller");
		break;
	case TYPE_ENCLOSURE:
		snprintf(label, LABEL_SIZE, "enclosure");
		break;
	case TYPE_DISK:
	case TYPE_ZBC:
		if (dev->external)
			snprintf(label, LABEL_SIZE, "external");
		else if (!is_logical_dev_addr_mode(dev->scsi3addr))
			snprintf(label, LABEL_SIZE, "%s",
				raid_label[PHYSICAL_DRIVE]);
		else
			snprintf(label, LABEL_SIZE, "RAID-%s",
				dev->raid_level > RAID_UNKNOWN ? "?" :
				raid_label[dev->raid_level]);
		break;
	case TYPE_ROM:
		snprintf(label, LABEL_SIZE, "rom");
		break;
	case TYPE_TAPE:
		snprintf(label, LABEL_SIZE, "tape");
		break;
	case TYPE_MEDIUM_CHANGER:
		snprintf(label, LABEL_SIZE, "changer");
		break;
	default:
		snprintf(label, LABEL_SIZE, "UNKNOWN");
		break;
	}

	dev_printk(level, &h->pdev->dev,
			"scsi %d:%d:%d:%d: %s %s %.8s %.16s %s SSDSmartPathCap%c En%c Exp=%d\n",
			h->scsi_host->host_no, dev->bus, dev->target, dev->lun,
			description,
			scsi_device_type(dev->devtype),
			dev->vendor,
			dev->model,
			label,
			dev->offload_config ? '+' : '-',
			dev->offload_to_be_enabled ? '+' : '-',
			dev->expose_device);
}