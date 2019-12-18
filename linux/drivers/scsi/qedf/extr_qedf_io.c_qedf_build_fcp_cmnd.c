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
struct scsi_lun {int dummy; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_1__* device; } ;
struct qedf_ioreq {scalar_t__ cmd_type; int /*<<< orphan*/  data_xfer_len; int /*<<< orphan*/  io_req_flags; int /*<<< orphan*/  tm_flags; struct scsi_cmnd* sc_cmd; } ;
struct fcp_cmnd {int /*<<< orphan*/  fc_dl; int /*<<< orphan*/  fc_cdb; scalar_t__ fc_pri_ta; int /*<<< orphan*/  fc_flags; scalar_t__ fc_cmdref; int /*<<< orphan*/  fc_tm_flags; int /*<<< orphan*/  fc_lun; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FCP_CFL_RDDATA ; 
 int /*<<< orphan*/  FCP_CFL_WRDATA ; 
 int /*<<< orphan*/  FCP_CMND_LEN ; 
 scalar_t__ FCP_PTA_SIMPLE ; 
 scalar_t__ QEDF_TASK_MGMT_CMD ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcp_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_build_fcp_cmnd(struct qedf_ioreq *io_req,
				  struct fcp_cmnd *fcp_cmnd)
{
	struct scsi_cmnd *sc_cmd = io_req->sc_cmd;

	/* fcp_cmnd is 32 bytes */
	memset(fcp_cmnd, 0, FCP_CMND_LEN);

	/* 8 bytes: SCSI LUN info */
	int_to_scsilun(sc_cmd->device->lun,
			(struct scsi_lun *)&fcp_cmnd->fc_lun);

	/* 4 bytes: flag info */
	fcp_cmnd->fc_pri_ta = 0;
	fcp_cmnd->fc_tm_flags = io_req->tm_flags;
	fcp_cmnd->fc_flags = io_req->io_req_flags;
	fcp_cmnd->fc_cmdref = 0;

	/* Populate data direction */
	if (io_req->cmd_type == QEDF_TASK_MGMT_CMD) {
		fcp_cmnd->fc_flags |= FCP_CFL_RDDATA;
	} else {
		if (sc_cmd->sc_data_direction == DMA_TO_DEVICE)
			fcp_cmnd->fc_flags |= FCP_CFL_WRDATA;
		else if (sc_cmd->sc_data_direction == DMA_FROM_DEVICE)
			fcp_cmnd->fc_flags |= FCP_CFL_RDDATA;
	}

	fcp_cmnd->fc_pri_ta = FCP_PTA_SIMPLE;

	/* 16 bytes: CDB information */
	if (io_req->cmd_type != QEDF_TASK_MGMT_CMD)
		memcpy(fcp_cmnd->fc_cdb, sc_cmd->cmnd, sc_cmd->cmd_len);

	/* 4 bytes: FCP data length */
	fcp_cmnd->fc_dl = htonl(io_req->data_xfer_len);
}