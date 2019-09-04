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
struct request {TYPE_1__* q; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq_zones_wlock; } ;

/* Variables and functions */
#define  REQ_OP_WRITE 130 
#define  REQ_OP_WRITE_SAME 129 
#define  REQ_OP_WRITE_ZEROES 128 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int blk_rq_zone_is_seq (struct request*) ; 
 int req_op (struct request*) ; 

bool blk_req_needs_zone_write_lock(struct request *rq)
{
	if (!rq->q->seq_zones_wlock)
		return false;

	if (blk_rq_is_passthrough(rq))
		return false;

	switch (req_op(rq)) {
	case REQ_OP_WRITE_ZEROES:
	case REQ_OP_WRITE_SAME:
	case REQ_OP_WRITE:
		return blk_rq_zone_is_seq(rq);
	default:
		return false;
	}
}