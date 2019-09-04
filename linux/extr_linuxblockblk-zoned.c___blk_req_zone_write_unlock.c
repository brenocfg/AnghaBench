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
struct request {TYPE_1__* q; int /*<<< orphan*/  rq_flags; } ;
struct TYPE_2__ {scalar_t__ seq_zones_wlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQF_ZONE_WRITE_LOCKED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  blk_rq_zone_no (struct request*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__) ; 

void __blk_req_zone_write_unlock(struct request *rq)
{
	rq->rq_flags &= ~RQF_ZONE_WRITE_LOCKED;
	if (rq->q->seq_zones_wlock)
		WARN_ON_ONCE(!test_and_clear_bit(blk_rq_zone_no(rq),
						 rq->q->seq_zones_wlock));
}