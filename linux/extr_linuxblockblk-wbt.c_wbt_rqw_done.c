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
struct rq_wb {int wb_background; int wb_normal; scalar_t__ wc; } ;
struct rq_wait {int /*<<< orphan*/  wait; int /*<<< orphan*/  inflight; } ;
typedef  enum wbt_flags { ____Placeholder_wbt_flags } wbt_flags ;

/* Variables and functions */
 int WBT_DISCARD ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwb_enabled (struct rq_wb*) ; 
 int /*<<< orphan*/  rwb_wake_all (struct rq_wb*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_recent_wait (struct rq_wb*) ; 
 scalar_t__ wq_has_sleeper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wbt_rqw_done(struct rq_wb *rwb, struct rq_wait *rqw,
			 enum wbt_flags wb_acct)
{
	int inflight, limit;

	inflight = atomic_dec_return(&rqw->inflight);

	/*
	 * wbt got disabled with IO in flight. Wake up any potential
	 * waiters, we don't have to do more than that.
	 */
	if (unlikely(!rwb_enabled(rwb))) {
		rwb_wake_all(rwb);
		return;
	}

	/*
	 * For discards, our limit is always the background. For writes, if
	 * the device does write back caching, drop further down before we
	 * wake people up.
	 */
	if (wb_acct & WBT_DISCARD)
		limit = rwb->wb_background;
	else if (rwb->wc && !wb_recent_wait(rwb))
		limit = 0;
	else
		limit = rwb->wb_normal;

	/*
	 * Don't wake anyone up if we are above the normal limit.
	 */
	if (inflight && inflight >= limit)
		return;

	if (wq_has_sleeper(&rqw->wait)) {
		int diff = limit - inflight;

		if (!inflight || diff >= rwb->wb_background / 2)
			wake_up_all(&rqw->wait);
	}
}