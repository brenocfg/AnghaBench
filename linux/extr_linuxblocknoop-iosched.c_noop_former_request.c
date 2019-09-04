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
struct request_queue {TYPE_1__* elevator; } ;
struct TYPE_4__ {int /*<<< orphan*/ * prev; } ;
struct request {TYPE_2__ queuelist; } ;
struct noop_data {int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {struct noop_data* elevator_data; } ;

/* Variables and functions */
 struct request* list_prev_entry (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queuelist ; 

__attribute__((used)) static struct request *
noop_former_request(struct request_queue *q, struct request *rq)
{
	struct noop_data *nd = q->elevator->elevator_data;

	if (rq->queuelist.prev == &nd->queue)
		return NULL;
	return list_prev_entry(rq, queuelist);
}