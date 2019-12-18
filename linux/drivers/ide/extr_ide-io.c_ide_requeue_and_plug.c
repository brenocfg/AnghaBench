#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/ * queue_hw_ctx; } ;
struct request {int dummy; } ;
struct TYPE_3__ {struct request_queue* queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_delay_kick_requeue_list (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_mq_delay_run_hw_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (struct request*,int) ; 

void ide_requeue_and_plug(ide_drive_t *drive, struct request *rq)
{
	struct request_queue *q = drive->queue;

	/* Use 3ms as that was the old plug delay */
	if (rq) {
		blk_mq_requeue_request(rq, false);
		blk_mq_delay_kick_requeue_list(q, 3);
	} else
		blk_mq_delay_run_hw_queue(q->queue_hw_ctx[0], 3);
}