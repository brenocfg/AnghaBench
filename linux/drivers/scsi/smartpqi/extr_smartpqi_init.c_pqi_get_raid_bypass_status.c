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
typedef  int u8 ;
struct pqi_scsi_dev {int raid_bypass_configured; int raid_bypass_enabled; int /*<<< orphan*/  scsi3addr; } ;
struct pqi_ctrl_info {int dummy; } ;

/* Variables and functions */
 int CISS_VPD_LV_BYPASS_STATUS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RAID_BYPASS_CONFIGURED ; 
 int RAID_BYPASS_ENABLED ; 
 size_t RAID_BYPASS_STATUS ; 
 int VPD_PAGE ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pqi_get_raid_map (struct pqi_ctrl_info*,struct pqi_scsi_dev*) ; 
 int pqi_scsi_inquiry (struct pqi_ctrl_info*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void pqi_get_raid_bypass_status(struct pqi_ctrl_info *ctrl_info,
	struct pqi_scsi_dev *device)
{
	int rc;
	u8 *buffer;
	u8 bypass_status;

	buffer = kmalloc(64, GFP_KERNEL);
	if (!buffer)
		return;

	rc = pqi_scsi_inquiry(ctrl_info, device->scsi3addr,
		VPD_PAGE | CISS_VPD_LV_BYPASS_STATUS, buffer, 64);
	if (rc)
		goto out;

#define RAID_BYPASS_STATUS	4
#define RAID_BYPASS_CONFIGURED	0x1
#define RAID_BYPASS_ENABLED	0x2

	bypass_status = buffer[RAID_BYPASS_STATUS];
	device->raid_bypass_configured =
		(bypass_status & RAID_BYPASS_CONFIGURED) != 0;
	if (device->raid_bypass_configured &&
		(bypass_status & RAID_BYPASS_ENABLED) &&
		pqi_get_raid_map(ctrl_info, device) == 0)
		device->raid_bypass_enabled = true;

out:
	kfree(buffer);
}