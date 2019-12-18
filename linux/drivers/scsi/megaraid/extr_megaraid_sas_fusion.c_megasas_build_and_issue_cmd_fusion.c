#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  SMID; } ;
union MEGASAS_REQUEST_DESCRIPTOR_UNION {TYPE_2__ SCSIIO; scalar_t__ Words; } ;
typedef  scalar_t__ u32 ;
struct scsi_cmnd {TYPE_5__* request; } ;
struct megasas_instance {scalar_t__ ldio_threshold; scalar_t__ max_fw_cmds; TYPE_3__* pdev; int /*<<< orphan*/  fw_outstanding; TYPE_1__* host; int /*<<< orphan*/  ldio_outstanding; } ;
struct megasas_cmd_fusion {scalar_t__ r1_alt_dev_handle; union MEGASAS_REQUEST_DESCRIPTOR_UNION* request_desc; TYPE_4__* io_request; scalar_t__ index; } ;
struct TYPE_10__ {scalar_t__ tag; } ;
struct TYPE_9__ {int ChainOffset; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ can_queue; } ;

/* Variables and functions */
 scalar_t__ MR_DEVHANDLE_INVALID ; 
 scalar_t__ READ_WRITE_LDIO ; 
 scalar_t__ SCSI_MLQUEUE_DEVICE_BUSY ; 
 scalar_t__ SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ megasas_build_io_fusion (struct megasas_instance*,struct scsi_cmnd*,struct megasas_cmd_fusion*) ; 
 scalar_t__ megasas_cmd_type (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  megasas_fire_cmd_fusion (struct megasas_instance*,union MEGASAS_REQUEST_DESCRIPTOR_UNION*) ; 
 struct megasas_cmd_fusion* megasas_get_cmd_fusion (struct megasas_instance*,scalar_t__) ; 
 union MEGASAS_REQUEST_DESCRIPTOR_UNION* megasas_get_request_descriptor (struct megasas_instance*,scalar_t__) ; 
 int /*<<< orphan*/  megasas_prepare_secondRaid1_IO (struct megasas_instance*,struct megasas_cmd_fusion*,struct megasas_cmd_fusion*) ; 
 int /*<<< orphan*/  megasas_return_cmd_fusion (struct megasas_instance*,struct megasas_cmd_fusion*) ; 

__attribute__((used)) static u32
megasas_build_and_issue_cmd_fusion(struct megasas_instance *instance,
				   struct scsi_cmnd *scmd)
{
	struct megasas_cmd_fusion *cmd, *r1_cmd = NULL;
	union MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;
	u32 index;

	if ((megasas_cmd_type(scmd) == READ_WRITE_LDIO) &&
		instance->ldio_threshold &&
		(atomic_inc_return(&instance->ldio_outstanding) >
		instance->ldio_threshold)) {
		atomic_dec(&instance->ldio_outstanding);
		return SCSI_MLQUEUE_DEVICE_BUSY;
	}

	if (atomic_inc_return(&instance->fw_outstanding) >
			instance->host->can_queue) {
		atomic_dec(&instance->fw_outstanding);
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	cmd = megasas_get_cmd_fusion(instance, scmd->request->tag);

	if (!cmd) {
		atomic_dec(&instance->fw_outstanding);
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	index = cmd->index;

	req_desc = megasas_get_request_descriptor(instance, index-1);

	req_desc->Words = 0;
	cmd->request_desc = req_desc;

	if (megasas_build_io_fusion(instance, scmd, cmd)) {
		megasas_return_cmd_fusion(instance, cmd);
		dev_err(&instance->pdev->dev, "Error building command\n");
		cmd->request_desc = NULL;
		atomic_dec(&instance->fw_outstanding);
		return SCSI_MLQUEUE_HOST_BUSY;
	}

	req_desc = cmd->request_desc;
	req_desc->SCSIIO.SMID = cpu_to_le16(index);

	if (cmd->io_request->ChainOffset != 0 &&
	    cmd->io_request->ChainOffset != 0xF)
		dev_err(&instance->pdev->dev, "The chain offset value is not "
		       "correct : %x\n", cmd->io_request->ChainOffset);
	/*
	 *	if it is raid 1/10 fp write capable.
	 *	try to get second command from pool and construct it.
	 *	From FW, it has confirmed that lba values of two PDs
	 *	corresponds to single R1/10 LD are always same
	 *
	 */
	/*	driver side count always should be less than max_fw_cmds
	 *	to get new command
	 */
	if (cmd->r1_alt_dev_handle != MR_DEVHANDLE_INVALID) {
		r1_cmd = megasas_get_cmd_fusion(instance,
				(scmd->request->tag + instance->max_fw_cmds));
		megasas_prepare_secondRaid1_IO(instance, cmd, r1_cmd);
	}


	/*
	 * Issue the command to the FW
	 */

	megasas_fire_cmd_fusion(instance, req_desc);

	if (r1_cmd)
		megasas_fire_cmd_fusion(instance, r1_cmd->request_desc);


	return 0;
}