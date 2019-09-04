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
struct swim_priv {int fdc_queue; size_t floppy_count; TYPE_2__* unit; } ;
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_4__ {TYPE_1__* disk; } ;
struct TYPE_3__ {struct request_queue* queue; } ;

/* Variables and functions */
 struct request* blk_fetch_request (struct request_queue*) ; 

__attribute__((used)) static struct request *swim_next_request(struct swim_priv *swd)
{
	struct request_queue *q;
	struct request *rq;
	int old_pos = swd->fdc_queue;

	do {
		q = swd->unit[swd->fdc_queue].disk->queue;
		if (++swd->fdc_queue == swd->floppy_count)
			swd->fdc_queue = 0;
		if (q) {
			rq = blk_fetch_request(q);
			if (rq)
				return rq;
		}
	} while (swd->fdc_queue != old_pos);

	return NULL;
}