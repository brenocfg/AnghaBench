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
struct pcd_unit {TYPE_1__* disk; scalar_t__ present; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int PCD_UNITS ; 
 int /*<<< orphan*/ * blk_fetch_request (struct request_queue*) ; 
 struct pcd_unit* pcd ; 
 int pcd_queue ; 
 int /*<<< orphan*/ * pcd_req ; 

__attribute__((used)) static int set_next_request(void)
{
	struct pcd_unit *cd;
	struct request_queue *q;
	int old_pos = pcd_queue;

	do {
		cd = &pcd[pcd_queue];
		q = cd->present ? cd->disk->queue : NULL;
		if (++pcd_queue == PCD_UNITS)
			pcd_queue = 0;
		if (q) {
			pcd_req = blk_fetch_request(q);
			if (pcd_req)
				break;
		}
	} while (pcd_queue != old_pos);

	return pcd_req != NULL;
}