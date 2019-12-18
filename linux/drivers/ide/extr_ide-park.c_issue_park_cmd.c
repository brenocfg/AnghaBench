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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_8__ {int dev_flags; unsigned long sleep; struct request_queue* queue; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_10__ {unsigned long* special; void* type; } ;
struct TYPE_9__ {int cmd_len; int /*<<< orphan*/ * cmd; scalar_t__ result; } ;

/* Variables and functions */
 void* ATA_PRIV_MISC ; 
 int /*<<< orphan*/  BLK_MQ_REQ_NOWAIT ; 
 int EIO ; 
 int IDE_DFLAG_PARKED ; 
 scalar_t__ IS_ERR (struct request*) ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  REQ_PARK_HEADS ; 
 int /*<<< orphan*/  REQ_UNPARK_HEADS ; 
 int /*<<< orphan*/  blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queues (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_insert_request_head (TYPE_2__*,struct request*) ; 
 int /*<<< orphan*/  ide_park_wq ; 
 TYPE_5__* ide_req (struct request*) ; 
 scalar_t__ jiffies ; 
 TYPE_3__* scsi_req (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void issue_park_cmd(ide_drive_t *drive, unsigned long timeout)
{
	ide_hwif_t *hwif = drive->hwif;
	struct request_queue *q = drive->queue;
	struct request *rq;
	int rc;

	timeout += jiffies;
	spin_lock_irq(&hwif->lock);
	if (drive->dev_flags & IDE_DFLAG_PARKED) {
		int reset_timer = time_before(timeout, drive->sleep);
		int start_queue = 0;

		drive->sleep = timeout;
		wake_up_all(&ide_park_wq);
		if (reset_timer && del_timer(&hwif->timer))
			start_queue = 1;
		spin_unlock_irq(&hwif->lock);

		if (start_queue)
			blk_mq_run_hw_queues(q, true);
		return;
	}
	spin_unlock_irq(&hwif->lock);

	rq = blk_get_request(q, REQ_OP_DRV_IN, 0);
	scsi_req(rq)->cmd[0] = REQ_PARK_HEADS;
	scsi_req(rq)->cmd_len = 1;
	ide_req(rq)->type = ATA_PRIV_MISC;
	ide_req(rq)->special = &timeout;
	blk_execute_rq(q, NULL, rq, 1);
	rc = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);
	if (rc)
		goto out;

	/*
	 * Make sure that *some* command is sent to the drive after the
	 * timeout has expired, so power management will be reenabled.
	 */
	rq = blk_get_request(q, REQ_OP_DRV_IN, BLK_MQ_REQ_NOWAIT);
	if (IS_ERR(rq))
		goto out;

	scsi_req(rq)->cmd[0] = REQ_UNPARK_HEADS;
	scsi_req(rq)->cmd_len = 1;
	ide_req(rq)->type = ATA_PRIV_MISC;
	spin_lock_irq(&hwif->lock);
	ide_insert_request_head(drive, rq);
	spin_unlock_irq(&hwif->lock);

out:
	return;
}