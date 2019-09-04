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
struct request {int /*<<< orphan*/  queuelist; scalar_t__ fifo_time; } ;
struct deadline_data {int /*<<< orphan*/ * fifo_list; scalar_t__* fifo_expire; } ;
struct TYPE_2__ {struct deadline_data* elevator_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_req_zone_write_unlock (struct request*) ; 
 int /*<<< orphan*/  deadline_add_rq_rb (struct deadline_data*,struct request*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rq_data_dir (struct request*) ; 

__attribute__((used)) static void
deadline_add_request(struct request_queue *q, struct request *rq)
{
	struct deadline_data *dd = q->elevator->elevator_data;
	const int data_dir = rq_data_dir(rq);

	/*
	 * This may be a requeue of a write request that has locked its
	 * target zone. If it is the case, this releases the zone lock.
	 */
	blk_req_zone_write_unlock(rq);

	deadline_add_rq_rb(dd, rq);

	/*
	 * set expire time and add to fifo list
	 */
	rq->fifo_time = jiffies + dd->fifo_expire[data_dir];
	list_add_tail(&rq->queuelist, &dd->fifo_list[data_dir]);
}