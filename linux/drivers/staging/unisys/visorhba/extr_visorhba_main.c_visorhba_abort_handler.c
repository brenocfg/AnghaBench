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
struct visordisk_info {int /*<<< orphan*/  ios_threshold; int /*<<< orphan*/  error_count; } ;
struct scsi_device {struct visordisk_info* hostdata; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;struct scsi_device* device; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int /*<<< orphan*/  IOS_ERROR_THRESHOLD ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TASK_MGMT_ABORT_TASK ; 
 scalar_t__ VISORHBA_ERROR_COUNT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int forward_taskmgmt_command (int /*<<< orphan*/ ,struct scsi_device*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int visorhba_abort_handler(struct scsi_cmnd *scsicmd)
{
	/* issue TASK_MGMT_ABORT_TASK */
	struct scsi_device *scsidev;
	struct visordisk_info *vdisk;
	int rtn;

	scsidev = scsicmd->device;
	vdisk = scsidev->hostdata;
	if (atomic_read(&vdisk->error_count) < VISORHBA_ERROR_COUNT)
		atomic_inc(&vdisk->error_count);
	else
		atomic_set(&vdisk->ios_threshold, IOS_ERROR_THRESHOLD);
	rtn = forward_taskmgmt_command(TASK_MGMT_ABORT_TASK, scsidev);
	if (rtn == SUCCESS) {
		scsicmd->result = DID_ABORT << 16;
		scsicmd->scsi_done(scsicmd);
	}
	return rtn;
}