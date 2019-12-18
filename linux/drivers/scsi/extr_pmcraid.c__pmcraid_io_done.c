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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  result; } ;
struct pmcraid_cmd {TYPE_1__* ioa_cb; struct scsi_cmnd* scsi_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cdb; int /*<<< orphan*/  response_handle; } ;
struct TYPE_3__ {TYPE_2__ ioarcb; } ;

/* Variables and functions */
 scalar_t__ PMCRAID_IOASC_SENSE_KEY (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int pmcraid_error_handler (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_info (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int _pmcraid_io_done(struct pmcraid_cmd *cmd, int reslen, int ioasc)
{
	struct scsi_cmnd *scsi_cmd = cmd->scsi_cmd;
	int rc = 0;

	scsi_set_resid(scsi_cmd, reslen);

	pmcraid_info("response(%d) CDB[0] = %x ioasc:result: %x:%x\n",
		le32_to_cpu(cmd->ioa_cb->ioarcb.response_handle) >> 2,
		cmd->ioa_cb->ioarcb.cdb[0],
		ioasc, scsi_cmd->result);

	if (PMCRAID_IOASC_SENSE_KEY(ioasc) != 0)
		rc = pmcraid_error_handler(cmd);

	if (rc == 0) {
		scsi_dma_unmap(scsi_cmd);
		scsi_cmd->scsi_done(scsi_cmd);
	}

	return rc;
}