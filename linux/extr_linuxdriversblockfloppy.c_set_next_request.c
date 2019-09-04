#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct TYPE_5__ {scalar_t__ error_count; } ;
struct TYPE_4__ {struct request_queue* queue; } ;

/* Variables and functions */
 int N_DRIVE ; 
 TYPE_2__* blk_fetch_request (struct request_queue*) ; 
 TYPE_2__* current_req ; 
 TYPE_1__** disks ; 
 int fdc_queue ; 

__attribute__((used)) static int set_next_request(void)
{
	struct request_queue *q;
	int old_pos = fdc_queue;

	do {
		q = disks[fdc_queue]->queue;
		if (++fdc_queue == N_DRIVE)
			fdc_queue = 0;
		if (q) {
			current_req = blk_fetch_request(q);
			if (current_req) {
				current_req->error_count = 0;
				break;
			}
		}
	} while (fdc_queue != old_pos);

	return current_req != NULL;
}