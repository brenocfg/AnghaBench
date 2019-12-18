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
typedef  scalar_t__ u16 ;
struct ScsiReqBlk {int flag; int /*<<< orphan*/  state; TYPE_1__* cmd; } ;
struct DeviceCtlBlk {int target_lun; } ;
struct AdapterCtlBlk {struct DeviceCtlBlk* active_dcb; } ;
struct TYPE_2__ {scalar_t__ cmd_len; scalar_t__ cmnd; } ;

/* Variables and functions */
 int AUTO_REQSENSE ; 
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DO_CLRATN ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int REQUEST_SENSE ; 
 int SCMD_FIFO_OUT ; 
 int SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SRB_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFO ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 

__attribute__((used)) static void command_phase1(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	struct DeviceCtlBlk *dcb;
	u8 *ptr;
	u16 i;
	dprintkdbg(DBG_0, "command_phase1: (0x%p)\n", srb->cmd);

	clear_fifo(acb, "command_phase1");
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_CLRATN);
	if (!(srb->flag & AUTO_REQSENSE)) {
		ptr = (u8 *)srb->cmd->cmnd;
		for (i = 0; i < srb->cmd->cmd_len; i++) {
			DC395x_write8(acb, TRM_S1040_SCSI_FIFO, *ptr);
			ptr++;
		}
	} else {
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, REQUEST_SENSE);
		dcb = acb->active_dcb;
		/* target id */
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, (dcb->target_lun << 5));
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, SCSI_SENSE_BUFFERSIZE);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, 0);
	}
	srb->state |= SRB_COMMAND;
	/* it's important for atn stop */
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
	/* SCSI command */
	DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
}