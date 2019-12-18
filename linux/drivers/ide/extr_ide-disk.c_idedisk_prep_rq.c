#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  cmd_flags; } ;
struct TYPE_8__ {int tf; } ;
struct TYPE_9__ {TYPE_2__ out; } ;
struct TYPE_7__ {int /*<<< orphan*/  command; } ;
struct ide_cmd {struct request* rq; int /*<<< orphan*/  protocol; int /*<<< orphan*/  tf_flags; TYPE_3__ valid; TYPE_1__ tf; } ;
struct TYPE_10__ {unsigned long capacity64; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ ide_drive_t ;
struct TYPE_11__ {struct ide_cmd* special; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_FLUSH ; 
 int /*<<< orphan*/  ATA_CMD_FLUSH_EXT ; 
 int /*<<< orphan*/  ATA_PRIV_TASKFILE ; 
 int /*<<< orphan*/  ATA_PROT_NODATA ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IDE_TFLAG_DYN ; 
 int IDE_VALID_DEVICE ; 
 int IDE_VALID_OUT_TF ; 
 int /*<<< orphan*/  REQ_OP_DRV_OUT ; 
 scalar_t__ REQ_OP_FLUSH ; 
 int /*<<< orphan*/  REQ_OP_MASK ; 
 scalar_t__ ata_id_flush_ext_enabled (int /*<<< orphan*/ ) ; 
 TYPE_6__* ide_req (struct request*) ; 
 struct ide_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ide_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ req_op (struct request*) ; 

__attribute__((used)) static bool idedisk_prep_rq(ide_drive_t *drive, struct request *rq)
{
	struct ide_cmd *cmd;

	if (req_op(rq) != REQ_OP_FLUSH)
		return true;

	if (ide_req(rq)->special) {
		cmd = ide_req(rq)->special;
		memset(cmd, 0, sizeof(*cmd));
	} else {
		cmd = kzalloc(sizeof(*cmd), GFP_ATOMIC);
	}

	/* FIXME: map struct ide_taskfile on rq->cmd[] */
	BUG_ON(cmd == NULL);

	if (ata_id_flush_ext_enabled(drive->id) &&
	    (drive->capacity64 >= (1UL << 28)))
		cmd->tf.command = ATA_CMD_FLUSH_EXT;
	else
		cmd->tf.command = ATA_CMD_FLUSH;
	cmd->valid.out.tf = IDE_VALID_OUT_TF | IDE_VALID_DEVICE;
	cmd->tf_flags = IDE_TFLAG_DYN;
	cmd->protocol = ATA_PROT_NODATA;
	rq->cmd_flags &= ~REQ_OP_MASK;
	rq->cmd_flags |= REQ_OP_DRV_OUT;
	ide_req(rq)->type = ATA_PRIV_TASKFILE;
	ide_req(rq)->special = cmd;
	cmd->rq = rq;

	return true;
}