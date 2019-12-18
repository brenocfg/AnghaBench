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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  rq_flags; struct request_queue* q; } ;
struct TYPE_2__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  blk_execute_rq (struct request_queue*,int /*<<< orphan*/ *,struct request*,int) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_dying (struct request_queue*) ; 
 TYPE_1__* scsi_req (struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ide_pm_execute_rq(struct request *rq)
{
	struct request_queue *q = rq->q;

	if (unlikely(blk_queue_dying(q))) {
		rq->rq_flags |= RQF_QUIET;
		scsi_req(rq)->result = -ENXIO;
		blk_mq_end_request(rq, BLK_STS_OK);
		return -ENXIO;
	}
	blk_execute_rq(q, NULL, rq, true);

	return scsi_req(rq)->result ? -EIO : 0;
}