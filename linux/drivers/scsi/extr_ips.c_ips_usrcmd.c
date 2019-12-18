#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_23__ {scalar_t__ op_code; void* sg_addr; int /*<<< orphan*/  command_id; } ;
struct TYPE_22__ {scalar_t__ op_code; void* dcdb_address; } ;
struct TYPE_18__ {int /*<<< orphan*/  cmd_attribute; TYPE_5__ basic_io; void* buffer_pointer; TYPE_4__ dcdb; } ;
struct TYPE_20__ {int /*<<< orphan*/  list; } ;
struct TYPE_25__ {int timeout; long data_busaddr; TYPE_6__* scsi_cmd; TYPE_11__ dcdb; TYPE_11__ cmd; int /*<<< orphan*/  scb_busaddr; scalar_t__ data_len; int /*<<< orphan*/  callback; scalar_t__ op_code; scalar_t__ flags; scalar_t__ sg_len; int /*<<< orphan*/  lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  bus; TYPE_2__ sg_list; } ;
typedef  TYPE_7__ ips_scb_t ;
struct TYPE_19__ {int /*<<< orphan*/  dcdb; int /*<<< orphan*/  cmd; } ;
struct TYPE_26__ {int TimeOut; scalar_t__ CmdBSize; TYPE_1__ CoppCP; } ;
typedef  TYPE_8__ ips_passthru_t ;
struct TYPE_27__ {long ioctl_busaddr; } ;
typedef  TYPE_9__ ips_ha_t ;
struct TYPE_24__ {int result; TYPE_3__* device; } ;
struct TYPE_21__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_17__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_10__ IPS_SG_LIST ;
typedef  int /*<<< orphan*/  IPS_IOCTL_CMD ;
typedef  int /*<<< orphan*/  IPS_DCDB_TABLE ;

/* Variables and functions */
 int DID_OK ; 
 scalar_t__ IPS_CMD_DCDB ; 
 scalar_t__ IPS_CMD_DCDB_SG ; 
 scalar_t__ IPS_CMD_READ_SG ; 
 scalar_t__ IPS_CMD_WRITE_SG ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_9__*,TYPE_7__*) ; 
 int /*<<< orphan*/  IPS_TIMEOUT10 ; 
 int /*<<< orphan*/  IPS_TIMEOUT20M ; 
 int /*<<< orphan*/  IPS_TIMEOUT60 ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 void* cpu_to_le32 (long) ; 
 int ips_cmd_timeout ; 
 int /*<<< orphan*/  ipsintr_done ; 
 int /*<<< orphan*/  memcpy (TYPE_11__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ips_usrcmd(ips_ha_t * ha, ips_passthru_t * pt, ips_scb_t * scb)
{
	IPS_SG_LIST sg_list;
	uint32_t cmd_busaddr;

	METHOD_TRACE("ips_usrcmd", 1);

	if ((!scb) || (!pt) || (!ha))
		return (0);

	/* Save the S/G list pointer so it doesn't get clobbered */
	sg_list.list = scb->sg_list.list;
	cmd_busaddr = scb->scb_busaddr;
	/* copy in the CP */
	memcpy(&scb->cmd, &pt->CoppCP.cmd, sizeof (IPS_IOCTL_CMD));
	memcpy(&scb->dcdb, &pt->CoppCP.dcdb, sizeof (IPS_DCDB_TABLE));

	/* FIX stuff that might be wrong */
	scb->sg_list.list = sg_list.list;
	scb->scb_busaddr = cmd_busaddr;
	scb->bus = scb->scsi_cmd->device->channel;
	scb->target_id = scb->scsi_cmd->device->id;
	scb->lun = scb->scsi_cmd->device->lun;
	scb->sg_len = 0;
	scb->data_len = 0;
	scb->flags = 0;
	scb->op_code = 0;
	scb->callback = ipsintr_done;
	scb->timeout = ips_cmd_timeout;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);

	/* we don't support DCDB/READ/WRITE Scatter Gather */
	if ((scb->cmd.basic_io.op_code == IPS_CMD_READ_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_WRITE_SG) ||
	    (scb->cmd.basic_io.op_code == IPS_CMD_DCDB_SG))
		return (0);

	if (pt->CmdBSize) {
		scb->data_len = pt->CmdBSize;
		scb->data_busaddr = ha->ioctl_busaddr + sizeof (ips_passthru_t);
	} else {
		scb->data_busaddr = 0L;
	}

	if (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
		scb->cmd.dcdb.dcdb_address = cpu_to_le32(scb->scb_busaddr +
							 (unsigned long) &scb->
							 dcdb -
							 (unsigned long) scb);

	if (pt->CmdBSize) {
		if (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)
			scb->dcdb.buffer_pointer =
			    cpu_to_le32(scb->data_busaddr);
		else
			scb->cmd.basic_io.sg_addr =
			    cpu_to_le32(scb->data_busaddr);
	}

	/* set timeouts */
	if (pt->TimeOut) {
		scb->timeout = pt->TimeOut;

		if (pt->TimeOut <= 10)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT10;
		else if (pt->TimeOut <= 60)
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT60;
		else
			scb->dcdb.cmd_attribute |= IPS_TIMEOUT20M;
	}

	/* assume success */
	scb->scsi_cmd->result = DID_OK << 16;

	/* success */
	return (1);
}