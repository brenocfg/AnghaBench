#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct TYPE_6__ {TYPE_2__* gendisk; TYPE_1__* type; } ;
struct TYPE_5__ {struct request_queue* queue; } ;
struct TYPE_4__ {scalar_t__ code; } ;

/* Variables and functions */
 int FD_MAX_UNITS ; 
 scalar_t__ FD_NODRIVE ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int fdc_queue ; 
 TYPE_3__* unit ; 

__attribute__((used)) static struct request *set_next_request(void)
{
	struct request_queue *q;
	int cnt = FD_MAX_UNITS;
	struct request *rq = NULL;

	/* Find next queue we can dispatch from */
	fdc_queue = fdc_queue + 1;
	if (fdc_queue == FD_MAX_UNITS)
		fdc_queue = 0;

	for(cnt = FD_MAX_UNITS; cnt > 0; cnt--) {

		if (unit[fdc_queue].type->code == FD_NODRIVE) {
			if (++fdc_queue == FD_MAX_UNITS)
				fdc_queue = 0;
			continue;
		}

		q = unit[fdc_queue].gendisk->queue;
		if (q) {
			rq = blk_fetch_request(q);
			if (rq)
				break;
		}

		if (++fdc_queue == FD_MAX_UNITS)
			fdc_queue = 0;
	}

	return rq;
}