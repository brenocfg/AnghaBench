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
struct request_queue {TYPE_1__* elevator; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;
struct bfq_data {int dummy; } ;
struct TYPE_2__ {struct bfq_data* elevator_data; } ;

/* Variables and functions */
 int ELEVATOR_FRONT_MERGE ; 
 int ELEVATOR_NO_MERGE ; 
 struct request* bfq_find_rq_fmerge (struct bfq_data*,struct bio*,struct request_queue*) ; 
 scalar_t__ elv_bio_merge_ok (struct request*,struct bio*) ; 

__attribute__((used)) static int bfq_request_merge(struct request_queue *q, struct request **req,
			     struct bio *bio)
{
	struct bfq_data *bfqd = q->elevator->elevator_data;
	struct request *__rq;

	__rq = bfq_find_rq_fmerge(bfqd, bio, q);
	if (__rq && elv_bio_merge_ok(__rq, bio)) {
		*req = __rq;
		return ELEVATOR_FRONT_MERGE;
	}

	return ELEVATOR_NO_MERGE;
}