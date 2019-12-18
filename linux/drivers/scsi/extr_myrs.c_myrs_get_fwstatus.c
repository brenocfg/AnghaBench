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
union myrs_sgl {TYPE_3__* sge; } ;
struct TYPE_9__ {int /*<<< orphan*/  dma_size; } ;
struct TYPE_6__ {int dma_ctrl_to_host; int no_autosense; } ;
struct TYPE_7__ {int dma_size; union myrs_sgl dma_addr; int /*<<< orphan*/  ioctl_opcode; TYPE_1__ control; int /*<<< orphan*/  id; int /*<<< orphan*/  opcode; } ;
union myrs_cmd_mbox {TYPE_4__ ctlr_info; TYPE_2__ common; } ;
struct myrs_cmdblk {unsigned char status; union myrs_cmd_mbox mbox; } ;
struct myrs_hba {TYPE_5__* host; int /*<<< orphan*/  fwstat_addr; struct myrs_cmdblk mcmd_blk; } ;
struct myrs_fwstat {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  shost_gendev; } ;
struct TYPE_8__ {int /*<<< orphan*/  sge_count; int /*<<< orphan*/  sge_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYRS_CMD_OP_IOCTL ; 
 int /*<<< orphan*/  MYRS_IOCTL_GET_HEALTH_STATUS ; 
 int /*<<< orphan*/  MYRS_MCMD_TAG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  myrs_exec_cmd (struct myrs_hba*,struct myrs_cmdblk*) ; 
 int /*<<< orphan*/  myrs_reset_cmd (struct myrs_cmdblk*) ; 

__attribute__((used)) static unsigned char myrs_get_fwstatus(struct myrs_hba *cs)
{
	struct myrs_cmdblk *cmd_blk = &cs->mcmd_blk;
	union myrs_cmd_mbox *mbox = &cmd_blk->mbox;
	union myrs_sgl *sgl;
	unsigned char status = cmd_blk->status;

	myrs_reset_cmd(cmd_blk);
	mbox->common.opcode = MYRS_CMD_OP_IOCTL;
	mbox->common.id = MYRS_MCMD_TAG;
	mbox->common.control.dma_ctrl_to_host = true;
	mbox->common.control.no_autosense = true;
	mbox->common.dma_size = sizeof(struct myrs_fwstat);
	mbox->common.ioctl_opcode = MYRS_IOCTL_GET_HEALTH_STATUS;
	sgl = &mbox->common.dma_addr;
	sgl->sge[0].sge_addr = cs->fwstat_addr;
	sgl->sge[0].sge_count = mbox->ctlr_info.dma_size;
	dev_dbg(&cs->host->shost_gendev, "Sending GetHealthStatus\n");
	myrs_exec_cmd(cs, cmd_blk);
	status = cmd_blk->status;

	return status;
}