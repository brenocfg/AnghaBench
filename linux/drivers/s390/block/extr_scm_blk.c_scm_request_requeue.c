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
struct scm_request {scalar_t__* request; struct scm_blk_dev* bdev; } ;
struct scm_blk_dev {int /*<<< orphan*/  rq; int /*<<< orphan*/  queued_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_kick_requeue_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_requeue_request (scalar_t__,int) ; 
 int nr_requests_per_io ; 
 int /*<<< orphan*/  scm_request_done (struct scm_request*) ; 

__attribute__((used)) static void scm_request_requeue(struct scm_request *scmrq)
{
	struct scm_blk_dev *bdev = scmrq->bdev;
	int i;

	for (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++)
		blk_mq_requeue_request(scmrq->request[i], false);

	atomic_dec(&bdev->queued_reqs);
	scm_request_done(scmrq);
	blk_mq_kick_requeue_list(bdev->rq);
}