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
struct request_queue {int dummy; } ;
struct request {scalar_t__ error_count; } ;
struct TYPE_4__ {TYPE_1__* disk; } ;
struct TYPE_3__ {struct request_queue* queue; } ;

/* Variables and functions */
 int FD_MAX_UNITS ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int fdc_queue ; 
 TYPE_2__* unit ; 

__attribute__((used)) static struct request *set_next_request(void)
{
	struct request_queue *q;
	int old_pos = fdc_queue;
	struct request *rq = NULL;

	do {
		q = unit[fdc_queue].disk->queue;
		if (++fdc_queue == FD_MAX_UNITS)
			fdc_queue = 0;
		if (q) {
			rq = blk_fetch_request(q);
			if (rq) {
				rq->error_count = 0;
				break;
			}
		}
	} while (fdc_queue != old_pos);

	return rq;
}