#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  __sector; int /*<<< orphan*/  rq_disk; } ;
struct TYPE_6__ {int blk_size; int valid; int /*<<< orphan*/  buf; int /*<<< orphan*/  cur; int /*<<< orphan*/  disk; int /*<<< orphan*/  first_frame; } ;
typedef  TYPE_1__ idetape_tape_t ;
struct TYPE_7__ {int /*<<< orphan*/  queue; TYPE_1__* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int* cmd; scalar_t__ result; scalar_t__ resid_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRIV_MISC ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  IDE_DBG_FUNC ; 
 scalar_t__ IDE_DRV_ERROR_GENERAL ; 
 int REQ_IDETAPE_READ ; 
 int REQ_IDETAPE_WRITE ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int blk_rq_map_kern (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_5__* ide_req (struct request*) ; 
 TYPE_3__* scsi_req (struct request*) ; 

__attribute__((used)) static int idetape_queue_rw_tail(ide_drive_t *drive, int cmd, int size)
{
	idetape_tape_t *tape = drive->driver_data;
	struct request *rq;
	int ret;

	ide_debug_log(IDE_DBG_FUNC, "cmd: 0x%x, size: %d", cmd, size);

	BUG_ON(cmd != REQ_IDETAPE_READ && cmd != REQ_IDETAPE_WRITE);
	BUG_ON(size < 0 || size % tape->blk_size);

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	scsi_req(rq)->cmd[13] = cmd;
	rq->rq_disk = tape->disk;
	rq->__sector = tape->first_frame;

	if (size) {
		ret = blk_rq_map_kern(drive->queue, rq, tape->buf, size,
				      GFP_NOIO);
		if (ret)
			goto out_put;
	}

	blk_execute_rq(drive->queue, tape->disk, rq, 0);

	/* calculate the number of transferred bytes and update buffer state */
	size -= scsi_req(rq)->resid_len;
	tape->cur = tape->buf;
	if (cmd == REQ_IDETAPE_READ)
		tape->valid = size;
	else
		tape->valid = 0;

	ret = size;
	if (scsi_req(rq)->result == IDE_DRV_ERROR_GENERAL)
		ret = -EIO;
out_put:
	blk_put_request(rq);
	return ret;
}