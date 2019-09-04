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
struct request_queue {int dummy; } ;
struct gendisk {struct request_queue* queue; } ;
struct TYPE_2__ {struct gendisk* gd; } ;

/* Variables and functions */
 int PD_UNITS ; 
 int /*<<< orphan*/ * blk_fetch_request (struct request_queue*) ; 
 TYPE_1__* pd ; 
 int pd_queue ; 
 int /*<<< orphan*/ * pd_req ; 

__attribute__((used)) static int set_next_request(void)
{
	struct gendisk *disk;
	struct request_queue *q;
	int old_pos = pd_queue;

	do {
		disk = pd[pd_queue].gd;
		q = disk ? disk->queue : NULL;
		if (++pd_queue == PD_UNITS)
			pd_queue = 0;
		if (q) {
			pd_req = blk_fetch_request(q);
			if (pd_req)
				break;
		}
	} while (pd_queue != old_pos);

	return pd_req != NULL;
}