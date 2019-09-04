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
struct rq_qos {TYPE_1__* ops; struct rq_qos* next; } ;
struct request_queue {struct rq_qos* rq_qos; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct rq_qos*,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rq_qos*,struct bio*) ; 

void rq_qos_cleanup(struct request_queue *q, struct bio *bio)
{
	struct rq_qos *rqos;

	for (rqos = q->rq_qos; rqos; rqos = rqos->next) {
		if (rqos->ops->cleanup)
			rqos->ops->cleanup(rqos, bio);
	}
}