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
struct scsi_cmnd {int result; scalar_t__ retries; TYPE_2__* request; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct hpsa_scsi_dev_t {scalar_t__ in_reset; scalar_t__ removed; } ;
struct ctlr_info {scalar_t__ acciopath_status; } ;
struct Scsi_Host {int dummy; } ;
struct CommandList {int dummy; } ;
struct TYPE_4__ {scalar_t__ tag; } ;
struct TYPE_3__ {struct hpsa_scsi_dev_t* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DID_NO_CONNECT ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (TYPE_2__*) ; 
 struct CommandList* cmd_tagged_alloc (struct ctlr_info*,struct scsi_cmnd*) ; 
 int hpsa_ciss_submit (struct ctlr_info*,struct CommandList*,struct scsi_cmnd*,struct hpsa_scsi_dev_t*) ; 
 int /*<<< orphan*/  hpsa_cmd_resolve_and_free (struct ctlr_info*,struct CommandList*) ; 
 int hpsa_ioaccel_submit (struct ctlr_info*,struct CommandList*,struct scsi_cmnd*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lockup_detected (struct ctlr_info*) ; 
 struct ctlr_info* sdev_to_hba (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_scsi_queue_command(struct Scsi_Host *sh, struct scsi_cmnd *cmd)
{
	struct ctlr_info *h;
	struct hpsa_scsi_dev_t *dev;
	struct CommandList *c;
	int rc = 0;

	/* Get the ptr to our adapter structure out of cmd->host. */
	h = sdev_to_hba(cmd->device);

	BUG_ON(cmd->request->tag < 0);

	dev = cmd->device->hostdata;
	if (!dev) {
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_done(cmd);
		return 0;
	}

	if (dev->removed) {
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_done(cmd);
		return 0;
	}

	if (unlikely(lockup_detected(h))) {
		cmd->result = DID_NO_CONNECT << 16;
		cmd->scsi_done(cmd);
		return 0;
	}

	if (dev->in_reset)
		return SCSI_MLQUEUE_DEVICE_BUSY;

	c = cmd_tagged_alloc(h, cmd);
	if (c == NULL)
		return SCSI_MLQUEUE_DEVICE_BUSY;

	/*
	 * This is necessary because the SML doesn't zero out this field during
	 * error recovery.
	 */
	cmd->result = 0;

	/*
	 * Call alternate submit routine for I/O accelerated commands.
	 * Retries always go down the normal I/O path.
	 */
	if (likely(cmd->retries == 0 &&
			!blk_rq_is_passthrough(cmd->request) &&
			h->acciopath_status)) {
		rc = hpsa_ioaccel_submit(h, c, cmd);
		if (rc == 0)
			return 0;
		if (rc == SCSI_MLQUEUE_HOST_BUSY) {
			hpsa_cmd_resolve_and_free(h, c);
			return SCSI_MLQUEUE_HOST_BUSY;
		}
	}
	return hpsa_ciss_submit(h, c, cmd, dev);
}