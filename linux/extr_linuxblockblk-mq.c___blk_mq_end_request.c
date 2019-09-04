#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct request {int rq_flags; struct request* next_rq; int /*<<< orphan*/  (* end_io ) (struct request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int RQF_STATS ; 
 int /*<<< orphan*/  blk_account_io_done (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_bidi_rq (struct request*) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 int /*<<< orphan*/  blk_mq_poll_stats_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_stat_add (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  rq_qos_done (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

inline void __blk_mq_end_request(struct request *rq, blk_status_t error)
{
	u64 now = ktime_get_ns();

	if (rq->rq_flags & RQF_STATS) {
		blk_mq_poll_stats_start(rq->q);
		blk_stat_add(rq, now);
	}

	blk_account_io_done(rq, now);

	if (rq->end_io) {
		rq_qos_done(rq->q, rq);
		rq->end_io(rq, error);
	} else {
		if (unlikely(blk_bidi_rq(rq)))
			blk_mq_free_request(rq->next_rq);
		blk_mq_free_request(rq);
	}
}