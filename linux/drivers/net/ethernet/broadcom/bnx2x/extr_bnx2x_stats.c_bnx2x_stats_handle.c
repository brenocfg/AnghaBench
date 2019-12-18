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
struct bnx2x {int stats_state; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  panic; } ;
typedef  enum bnx2x_stats_state { ____Placeholder_bnx2x_stats_state } bnx2x_stats_state ;
typedef  enum bnx2x_stats_event { ____Placeholder_bnx2x_stats_event } bnx2x_stats_event ;
struct TYPE_2__ {int next_state; int /*<<< orphan*/  (* action ) (struct bnx2x*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_STATS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,...) ; 
 int HZ ; 
 int STATS_EVENT_UPDATE ; 
 TYPE_1__** bnx2x_stats_stm ; 
 int /*<<< orphan*/  down_timeout (int /*<<< orphan*/ *,int) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_msg_timer (struct bnx2x*) ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void bnx2x_stats_handle(struct bnx2x *bp, enum bnx2x_stats_event event)
{
	enum bnx2x_stats_state state = bp->stats_state;

	if (unlikely(bp->panic))
		return;

	/* Statistics update run from timer context, and we don't want to stop
	 * that context in case someone is in the middle of a transition.
	 * For other events, wait a bit until lock is taken.
	 */
	if (down_trylock(&bp->stats_lock)) {
		if (event == STATS_EVENT_UPDATE)
			return;

		DP(BNX2X_MSG_STATS,
		   "Unlikely stats' lock contention [event %d]\n", event);
		if (unlikely(down_timeout(&bp->stats_lock, HZ / 10))) {
			BNX2X_ERR("Failed to take stats lock [event %d]\n",
				  event);
			return;
		}
	}

	bnx2x_stats_stm[state][event].action(bp);
	bp->stats_state = bnx2x_stats_stm[state][event].next_state;

	up(&bp->stats_lock);

	if ((event != STATS_EVENT_UPDATE) || netif_msg_timer(bp))
		DP(BNX2X_MSG_STATS, "state %d -> event %d -> state %d\n",
		   state, event, bp->stats_state);
}