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
struct request_queue {int /*<<< orphan*/  poll_cb; int /*<<< orphan*/  queue_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_POLL_STATS ; 
 int /*<<< orphan*/  blk_stat_activate_msecs (int /*<<< orphan*/ ,int) ; 
 scalar_t__ blk_stat_is_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blk_mq_poll_stats_start(struct request_queue *q)
{
	/*
	 * We don't arm the callback if polling stats are not enabled or the
	 * callback is already active.
	 */
	if (!test_bit(QUEUE_FLAG_POLL_STATS, &q->queue_flags) ||
	    blk_stat_is_active(q->poll_cb))
		return;

	blk_stat_activate_msecs(q->poll_cb, 100);
}