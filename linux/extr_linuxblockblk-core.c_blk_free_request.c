#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_list {int /*<<< orphan*/  rq_pool; int /*<<< orphan*/  q; } ;
struct TYPE_4__ {TYPE_1__* icq; } ;
struct request {int rq_flags; TYPE_2__ elv; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int RQF_ELVPRIV ; 
 int /*<<< orphan*/  elv_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  mempool_free (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_io_context (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void blk_free_request(struct request_list *rl, struct request *rq)
{
	if (rq->rq_flags & RQF_ELVPRIV) {
		elv_put_request(rl->q, rq);
		if (rq->elv.icq)
			put_io_context(rq->elv.icq->ioc);
	}

	mempool_free(rq, rl->rq_pool);
}