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
struct pf_unit {TYPE_1__* disk; scalar_t__ present; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int PF_UNITS ; 
 int /*<<< orphan*/ * blk_fetch_request (struct request_queue*) ; 
 int pf_queue ; 
 int /*<<< orphan*/ * pf_req ; 
 struct pf_unit* units ; 

__attribute__((used)) static int set_next_request(void)
{
	struct pf_unit *pf;
	struct request_queue *q;
	int old_pos = pf_queue;

	do {
		pf = &units[pf_queue];
		q = pf->present ? pf->disk->queue : NULL;
		if (++pf_queue == PF_UNITS)
			pf_queue = 0;
		if (q) {
			pf_req = blk_fetch_request(q);
			if (pf_req)
				break;
		}
	} while (pf_queue != old_pos);

	return pf_req != NULL;
}