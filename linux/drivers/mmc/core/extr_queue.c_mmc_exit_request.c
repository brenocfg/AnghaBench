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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct mmc_queue_req {int /*<<< orphan*/ * sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct mmc_queue_req* req_to_mmc_queue_req (struct request*) ; 

__attribute__((used)) static void mmc_exit_request(struct request_queue *q, struct request *req)
{
	struct mmc_queue_req *mq_rq = req_to_mmc_queue_req(req);

	kfree(mq_rq->sg);
	mq_rq->sg = NULL;
}