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
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  sc_data_direction; int /*<<< orphan*/  sense_buffer; TYPE_1__ SCp; } ;
struct mvumi_sense_data {int dummy; } ;
struct mvumi_rsp_frame {int req_status; int rsp_flag; int /*<<< orphan*/  payload; } ;
struct mvumi_hba {TYPE_2__* pdev; } ;
struct mvumi_cmd {struct scsi_cmnd* scmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CL_RSP_FLAG_SENSEDATA ; 
 int DID_ABORT ; 
 int DID_BUS_BUSY ; 
 int DID_OK ; 
 int DRIVER_INVALID ; 
 int DRIVER_SENSE ; 
#define  SAM_STAT_BUSY 130 
#define  SAM_STAT_CHECK_CONDITION 129 
#define  SAM_STAT_GOOD 128 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvumi_return_cmd (struct mvumi_hba*,struct mvumi_cmd*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void mvumi_complete_cmd(struct mvumi_hba *mhba, struct mvumi_cmd *cmd,
					struct mvumi_rsp_frame *ob_frame)
{
	struct scsi_cmnd *scmd = cmd->scmd;

	cmd->scmd->SCp.ptr = NULL;
	scmd->result = ob_frame->req_status;

	switch (ob_frame->req_status) {
	case SAM_STAT_GOOD:
		scmd->result |= DID_OK << 16;
		break;
	case SAM_STAT_BUSY:
		scmd->result |= DID_BUS_BUSY << 16;
		break;
	case SAM_STAT_CHECK_CONDITION:
		scmd->result |= (DID_OK << 16);
		if (ob_frame->rsp_flag & CL_RSP_FLAG_SENSEDATA) {
			memcpy(cmd->scmd->sense_buffer, ob_frame->payload,
				sizeof(struct mvumi_sense_data));
			scmd->result |=  (DRIVER_SENSE << 24);
		}
		break;
	default:
		scmd->result |= (DRIVER_INVALID << 24) | (DID_ABORT << 16);
		break;
	}

	if (scsi_bufflen(scmd))
		dma_unmap_sg(&mhba->pdev->dev, scsi_sglist(scmd),
			     scsi_sg_count(scmd),
			     scmd->sc_data_direction);
	cmd->scmd->scsi_done(scmd);
	mvumi_return_cmd(mhba, cmd);
}