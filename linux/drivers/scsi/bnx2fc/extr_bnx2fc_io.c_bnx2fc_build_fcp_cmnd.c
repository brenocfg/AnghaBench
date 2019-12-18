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
struct scsi_cmnd {int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_1__* device; } ;
struct fcp_cmnd {scalar_t__ fc_pri_ta; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_tm_flags; scalar_t__ fc_cmdref; int /*<<< orphan*/  fc_cdb; int /*<<< orphan*/  fc_dl; int /*<<< orphan*/  fc_lun; } ;
struct TYPE_4__ {int /*<<< orphan*/  tm_flags; } ;
struct bnx2fc_cmd {int /*<<< orphan*/  io_req_flags; TYPE_2__ mp_req; int /*<<< orphan*/  data_xfer_len; struct scsi_cmnd* sc_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  lun; } ;

/* Variables and functions */
 scalar_t__ FCP_PTA_SIMPLE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fcp_cmnd*,int /*<<< orphan*/ ,int) ; 

void bnx2fc_build_fcp_cmnd(struct bnx2fc_cmd *io_req,
				  struct fcp_cmnd *fcp_cmnd)
{
	struct scsi_cmnd *sc_cmd = io_req->sc_cmd;

	memset(fcp_cmnd, 0, sizeof(struct fcp_cmnd));

	int_to_scsilun(sc_cmd->device->lun, &fcp_cmnd->fc_lun);

	fcp_cmnd->fc_dl = htonl(io_req->data_xfer_len);
	memcpy(fcp_cmnd->fc_cdb, sc_cmd->cmnd, sc_cmd->cmd_len);

	fcp_cmnd->fc_cmdref = 0;
	fcp_cmnd->fc_pri_ta = 0;
	fcp_cmnd->fc_tm_flags = io_req->mp_req.tm_flags;
	fcp_cmnd->fc_flags = io_req->io_req_flags;
	fcp_cmnd->fc_pri_ta = FCP_PTA_SIMPLE;
}