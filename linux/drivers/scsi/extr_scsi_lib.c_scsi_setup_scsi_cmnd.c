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
struct scsi_device {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  allowed; int /*<<< orphan*/  transfersize; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  sdb; } ;
struct request {scalar_t__ bio; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  retries; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmd_len; } ;

/* Variables and functions */
 scalar_t__ BLK_STS_OK ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct scsi_cmnd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_init_io (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_req (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_status_t scsi_setup_scsi_cmnd(struct scsi_device *sdev,
		struct request *req)
{
	struct scsi_cmnd *cmd = blk_mq_rq_to_pdu(req);

	/*
	 * Passthrough requests may transfer data, in which case they must
	 * a bio attached to them.  Or they might contain a SCSI command
	 * that does not transfer data, in which case they may optionally
	 * submit a request without an attached bio.
	 */
	if (req->bio) {
		blk_status_t ret = scsi_init_io(cmd);
		if (unlikely(ret != BLK_STS_OK))
			return ret;
	} else {
		BUG_ON(blk_rq_bytes(req));

		memset(&cmd->sdb, 0, sizeof(cmd->sdb));
	}

	cmd->cmd_len = scsi_req(req)->cmd_len;
	cmd->cmnd = scsi_req(req)->cmd;
	cmd->transfersize = blk_rq_bytes(req);
	cmd->allowed = scsi_req(req)->retries;
	return BLK_STS_OK;
}