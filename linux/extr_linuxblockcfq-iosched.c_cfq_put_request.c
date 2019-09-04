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
struct TYPE_2__ {int /*<<< orphan*/ ** priv; } ;
struct request {TYPE_1__ elv; } ;
struct cfq_queue {int /*<<< orphan*/ * allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 struct cfq_queue* RQ_CFQQ (struct request*) ; 
 int /*<<< orphan*/  cfq_put_queue (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfqg_put (int /*<<< orphan*/ ) ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static void cfq_put_request(struct request *rq)
{
	struct cfq_queue *cfqq = RQ_CFQQ(rq);

	if (cfqq) {
		const int rw = rq_data_dir(rq);

		BUG_ON(!cfqq->allocated[rw]);
		cfqq->allocated[rw]--;

		/* Put down rq reference on cfqg */
		cfqg_put(RQ_CFQG(rq));
		rq->elv.priv[0] = NULL;
		rq->elv.priv[1] = NULL;

		cfq_put_queue(cfqq);
	}
}