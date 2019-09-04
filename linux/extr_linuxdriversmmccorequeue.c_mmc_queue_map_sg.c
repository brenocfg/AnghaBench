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
struct request {int dummy; } ;
struct mmc_queue_req {int /*<<< orphan*/  sg; } ;
struct mmc_queue {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 unsigned int blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* mmc_queue_req_to_req (struct mmc_queue_req*) ; 

unsigned int mmc_queue_map_sg(struct mmc_queue *mq, struct mmc_queue_req *mqrq)
{
	struct request *req = mmc_queue_req_to_req(mqrq);

	return blk_rq_map_sg(mq->queue, req, mqrq->sg);
}