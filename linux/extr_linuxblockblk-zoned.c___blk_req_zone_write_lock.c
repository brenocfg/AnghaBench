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
struct request {int rq_flags; TYPE_1__* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_zones_wlock; } ;

/* Variables and functions */
 int RQF_ZONE_WRITE_LOCKED ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_rq_zone_no (struct request*) ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __blk_req_zone_write_lock(struct request *rq)
{
	if (WARN_ON_ONCE(test_and_set_bit(blk_rq_zone_no(rq),
					  rq->q->seq_zones_wlock)))
		return;

	WARN_ON_ONCE(rq->rq_flags & RQF_ZONE_WRITE_LOCKED);
	rq->rq_flags |= RQF_ZONE_WRITE_LOCKED;
}