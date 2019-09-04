#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct request_queue {struct memstick_dev* queuedata; } ;
struct request {int dummy; } ;
struct msb_data {int /*<<< orphan*/  io_work; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  io_queue_stopped; scalar_t__ req; scalar_t__ card_dead; } ;
struct memstick_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dbg_verbose (char*) ; 
 struct msb_data* memstick_get_drvdata (struct memstick_dev*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msb_submit_req(struct request_queue *q)
{
	struct memstick_dev *card = q->queuedata;
	struct msb_data *msb = memstick_get_drvdata(card);
	struct request *req = NULL;

	dbg_verbose("Submit request");

	if (msb->card_dead) {
		dbg("Refusing requests on removed card");

		WARN_ON(!msb->io_queue_stopped);

		while ((req = blk_fetch_request(q)) != NULL)
			__blk_end_request_all(req, BLK_STS_IOERR);
		return;
	}

	if (msb->req)
		return;

	if (!msb->io_queue_stopped)
		queue_work(msb->io_queue, &msb->io_work);
}