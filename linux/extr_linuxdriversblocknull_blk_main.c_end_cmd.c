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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct nullb_cmd {TYPE_5__* bio; int /*<<< orphan*/  error; TYPE_3__* rq; TYPE_2__* nq; } ;
struct TYPE_9__ {int /*<<< orphan*/  bi_status; } ;
struct TYPE_8__ {int /*<<< orphan*/  queuelist; struct request_queue* q; } ;
struct TYPE_7__ {TYPE_1__* dev; } ;
struct TYPE_6__ {int queue_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  NULL_Q_BIO 130 
#define  NULL_Q_MQ 129 
#define  NULL_Q_RQ 128 
 int /*<<< orphan*/  bio_endio (TYPE_5__*) ; 
 int /*<<< orphan*/  blk_end_request_all (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_end_request (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_stopped (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_queue_async (struct request_queue*) ; 
 int /*<<< orphan*/  free_cmd (struct nullb_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void end_cmd(struct nullb_cmd *cmd)
{
	struct request_queue *q = NULL;
	int queue_mode = cmd->nq->dev->queue_mode;

	if (cmd->rq)
		q = cmd->rq->q;

	switch (queue_mode)  {
	case NULL_Q_MQ:
		blk_mq_end_request(cmd->rq, cmd->error);
		return;
	case NULL_Q_RQ:
		INIT_LIST_HEAD(&cmd->rq->queuelist);
		blk_end_request_all(cmd->rq, cmd->error);
		break;
	case NULL_Q_BIO:
		cmd->bio->bi_status = cmd->error;
		bio_endio(cmd->bio);
		break;
	}

	free_cmd(cmd);

	/* Restart queue if needed, as we are freeing a tag */
	if (queue_mode == NULL_Q_RQ && blk_queue_stopped(q)) {
		unsigned long flags;

		spin_lock_irqsave(q->queue_lock, flags);
		blk_start_queue_async(q);
		spin_unlock_irqrestore(q->queue_lock, flags);
	}
}