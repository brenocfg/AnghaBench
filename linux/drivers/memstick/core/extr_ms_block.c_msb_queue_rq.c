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
struct request {int dummy; } ;
struct msb_data {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  io_work; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  io_queue_stopped; struct request* req; scalar_t__ card_dead; } ;
struct memstick_dev {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct memstick_dev* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t msb_queue_rq(struct blk_mq_hw_ctx *hctx,
				 const struct blk_mq_queue_data *bd)
{
	struct memstick_dev *card = hctx->queue->queuedata;
	struct msb_data *msb = memstick_get_drvdata(card);
	struct request *req = bd->rq;

	dbg_verbose("Submit request");

	spin_lock_irq(&msb->q_lock);

	if (msb->card_dead) {
		dbg("Refusing requests on removed card");

		WARN_ON(!msb->io_queue_stopped);

		spin_unlock_irq(&msb->q_lock);
		blk_mq_start_request(req);
		return BLK_STS_IOERR;
	}

	if (msb->req) {
		spin_unlock_irq(&msb->q_lock);
		return BLK_STS_DEV_RESOURCE;
	}

	blk_mq_start_request(req);
	msb->req = req;

	if (!msb->io_queue_stopped)
		queue_work(msb->io_queue, &msb->io_work);

	spin_unlock_irq(&msb->q_lock);
	return BLK_STS_OK;
}