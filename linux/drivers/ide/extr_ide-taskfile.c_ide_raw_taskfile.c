#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct request {int dummy; } ;
struct ide_cmd {int tf_flags; struct request* rq; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_7__ {struct ide_cmd* special; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRIV_TASKFILE ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int IDE_TFLAG_WRITE ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  REQ_OP_DRV_OUT ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* ide_req (struct request*) ; 
 TYPE_2__* scsi_req (struct request*) ; 

int ide_raw_taskfile(ide_drive_t *drive, struct ide_cmd *cmd, u8 *buf,
		     u16 nsect)
{
	struct request *rq;
	int error;

	rq = blk_get_request(drive->queue,
		(cmd->tf_flags & IDE_TFLAG_WRITE) ?
			REQ_OP_DRV_OUT : REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_TASKFILE;

	/*
	 * (ks) We transfer currently only whole sectors.
	 * This is suffient for now.  But, it would be great,
	 * if we would find a solution to transfer any size.
	 * To support special commands like READ LONG.
	 */
	if (nsect) {
		error = blk_rq_map_kern(drive->queue, rq, buf,
					nsect * SECTOR_SIZE, GFP_NOIO);
		if (error)
			goto put_req;
	}

	ide_req(rq)->special = cmd;
	cmd->rq = rq;

	blk_execute_rq(drive->queue, NULL, rq, 0);
	error = scsi_req(rq)->result ? -EIO : 0;
put_req:
	blk_put_request(rq);
	return error;
}