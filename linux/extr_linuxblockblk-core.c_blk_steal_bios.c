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
struct request {scalar_t__ __data_len; TYPE_1__* biotail; int /*<<< orphan*/ * bio; } ;
struct bio_list {TYPE_1__* tail; int /*<<< orphan*/ * head; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bi_next; } ;

/* Variables and functions */

void blk_steal_bios(struct bio_list *list, struct request *rq)
{
	if (rq->bio) {
		if (list->tail)
			list->tail->bi_next = rq->bio;
		else
			list->head = rq->bio;
		list->tail = rq->biotail;

		rq->bio = NULL;
		rq->biotail = NULL;
	}

	rq->__data_len = 0;
}