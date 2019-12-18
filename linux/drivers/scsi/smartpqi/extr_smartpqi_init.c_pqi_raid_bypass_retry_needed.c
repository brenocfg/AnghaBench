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
struct scsi_cmnd {int result; TYPE_1__* device; } ;
struct pqi_scsi_dev {int dummy; } ;
struct pqi_io_request {struct scsi_cmnd* scmd; int /*<<< orphan*/  raid_bypass; } ;
struct pqi_ctrl_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; struct pqi_scsi_dev* hostdata; } ;

/* Variables and functions */
 scalar_t__ DID_NO_CONNECT ; 
 int SAM_STAT_GOOD ; 
 scalar_t__ host_byte (int) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_device_offline (struct pqi_scsi_dev*) ; 
 struct pqi_ctrl_info* shost_to_hba (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pqi_raid_bypass_retry_needed(struct pqi_io_request *io_request)
{
	struct scsi_cmnd *scmd;
	struct pqi_scsi_dev *device;
	struct pqi_ctrl_info *ctrl_info;

	if (!io_request->raid_bypass)
		return false;

	scmd = io_request->scmd;
	if ((scmd->result & 0xff) == SAM_STAT_GOOD)
		return false;
	if (host_byte(scmd->result) == DID_NO_CONNECT)
		return false;

	device = scmd->device->hostdata;
	if (pqi_device_offline(device))
		return false;

	ctrl_info = shost_to_hba(scmd->device->host);
	if (pqi_ctrl_offline(ctrl_info))
		return false;

	return true;
}