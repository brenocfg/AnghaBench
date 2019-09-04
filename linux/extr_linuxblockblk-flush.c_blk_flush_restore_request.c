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
struct TYPE_2__ {int /*<<< orphan*/  saved_end_io; } ;
struct request {TYPE_1__ flush; int /*<<< orphan*/  end_io; int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  biotail; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQF_FLUSH_SEQ ; 

__attribute__((used)) static void blk_flush_restore_request(struct request *rq)
{
	/*
	 * After flush data completion, @rq->bio is %NULL but we need to
	 * complete the bio again.  @rq->biotail is guaranteed to equal the
	 * original @rq->bio.  Restore it.
	 */
	rq->bio = rq->biotail;

	/* make @rq a normal request */
	rq->rq_flags &= ~RQF_FLUSH_SEQ;
	rq->end_io = rq->flush.saved_end_io;
}