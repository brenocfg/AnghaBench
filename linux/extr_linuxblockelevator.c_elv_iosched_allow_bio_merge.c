#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct elevator_queue* elevator; } ;
struct request {struct request_queue* q; } ;
struct elevator_queue {TYPE_3__* type; scalar_t__ uses_mq; } ;
struct bio {int dummy; } ;
struct TYPE_8__ {int (* allow_merge ) (struct request_queue*,struct request*,struct bio*) ;} ;
struct TYPE_5__ {int (* elevator_allow_bio_merge_fn ) (struct request_queue*,struct request*,struct bio*) ;} ;
struct TYPE_6__ {TYPE_1__ sq; TYPE_4__ mq; } ;
struct TYPE_7__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int stub1 (struct request_queue*,struct request*,struct bio*) ; 
 int stub2 (struct request_queue*,struct request*,struct bio*) ; 

__attribute__((used)) static int elv_iosched_allow_bio_merge(struct request *rq, struct bio *bio)
{
	struct request_queue *q = rq->q;
	struct elevator_queue *e = q->elevator;

	if (e->uses_mq && e->type->ops.mq.allow_merge)
		return e->type->ops.mq.allow_merge(q, rq, bio);
	else if (!e->uses_mq && e->type->ops.sq.elevator_allow_bio_merge_fn)
		return e->type->ops.sq.elevator_allow_bio_merge_fn(q, rq, bio);

	return 1;
}