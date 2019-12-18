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
struct scm_request {scalar_t__* request; int /*<<< orphan*/  error; struct scm_blk_dev* bdev; } ;
struct scm_blk_dev {int /*<<< orphan*/  queued_reqs; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_complete_request (scalar_t__) ; 
 int /*<<< orphan*/ * blk_mq_rq_to_pdu (scalar_t__) ; 
 int nr_requests_per_io ; 
 int /*<<< orphan*/  scm_request_done (struct scm_request*) ; 

__attribute__((used)) static void scm_request_finish(struct scm_request *scmrq)
{
	struct scm_blk_dev *bdev = scmrq->bdev;
	blk_status_t *error;
	int i;

	for (i = 0; i < nr_requests_per_io && scmrq->request[i]; i++) {
		error = blk_mq_rq_to_pdu(scmrq->request[i]);
		*error = scmrq->error;
		blk_mq_complete_request(scmrq->request[i]);
	}

	atomic_dec(&bdev->queued_reqs);
	scm_request_done(scmrq);
}