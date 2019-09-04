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
struct request_queue {struct carm_host* queuedata; } ;
struct request {struct carm_request* special; } ;
struct carm_request {scalar_t__ n_elem; struct request* rq; } ;
struct carm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_requeue_request (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  carm_push_q (struct carm_host*,struct request_queue*) ; 
 int carm_send_msg (struct carm_host*,struct carm_request*) ; 

__attribute__((used)) static void carm_oob_rq_fn(struct request_queue *q)
{
	struct carm_host *host = q->queuedata;
	struct carm_request *crq;
	struct request *rq;
	int rc;

	while (1) {
		DPRINTK("get req\n");
		rq = blk_fetch_request(q);
		if (!rq)
			break;

		crq = rq->special;
		assert(crq != NULL);
		assert(crq->rq == rq);

		crq->n_elem = 0;

		DPRINTK("send req\n");
		rc = carm_send_msg(host, crq);
		if (rc) {
			blk_requeue_request(q, rq);
			carm_push_q(host, q);
			return;		/* call us again later, eventually */
		}
	}
}