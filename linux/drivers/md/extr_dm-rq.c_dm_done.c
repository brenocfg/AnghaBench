#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_3__* q; struct dm_rq_target_io* end_io_data; } ;
struct dm_rq_target_io {int /*<<< orphan*/  md; int /*<<< orphan*/  info; TYPE_4__* ti; } ;
typedef  int (* dm_request_endio_fn ) (TYPE_4__*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_8__ {TYPE_1__* type; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_write_zeroes_sectors; int /*<<< orphan*/  max_write_same_sectors; int /*<<< orphan*/  max_discard_sectors; } ;
struct TYPE_7__ {TYPE_2__ limits; } ;
struct TYPE_5__ {int (* rq_end_io ) (TYPE_4__*,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_TARGET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMWARN (char*,int) ; 
#define  DM_ENDIO_DELAY_REQUEUE 131 
#define  DM_ENDIO_DONE 130 
#define  DM_ENDIO_INCOMPLETE 129 
#define  DM_ENDIO_REQUEUE 128 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_WRITE_SAME ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int /*<<< orphan*/  disable_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_write_same (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_write_zeroes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_requeue_original_request (struct dm_rq_target_io*,int) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void dm_done(struct request *clone, blk_status_t error, bool mapped)
{
	int r = DM_ENDIO_DONE;
	struct dm_rq_target_io *tio = clone->end_io_data;
	dm_request_endio_fn rq_end_io = NULL;

	if (tio->ti) {
		rq_end_io = tio->ti->type->rq_end_io;

		if (mapped && rq_end_io)
			r = rq_end_io(tio->ti, clone, error, &tio->info);
	}

	if (unlikely(error == BLK_STS_TARGET)) {
		if (req_op(clone) == REQ_OP_DISCARD &&
		    !clone->q->limits.max_discard_sectors)
			disable_discard(tio->md);
		else if (req_op(clone) == REQ_OP_WRITE_SAME &&
			 !clone->q->limits.max_write_same_sectors)
			disable_write_same(tio->md);
		else if (req_op(clone) == REQ_OP_WRITE_ZEROES &&
			 !clone->q->limits.max_write_zeroes_sectors)
			disable_write_zeroes(tio->md);
	}

	switch (r) {
	case DM_ENDIO_DONE:
		/* The target wants to complete the I/O */
		dm_end_request(clone, error);
		break;
	case DM_ENDIO_INCOMPLETE:
		/* The target will handle the I/O */
		return;
	case DM_ENDIO_REQUEUE:
		/* The target wants to requeue the I/O */
		dm_requeue_original_request(tio, false);
		break;
	case DM_ENDIO_DELAY_REQUEUE:
		/* The target wants to requeue the I/O after a delay */
		dm_requeue_original_request(tio, true);
		break;
	default:
		DMWARN("unimplemented target endio return value: %d", r);
		BUG();
	}
}