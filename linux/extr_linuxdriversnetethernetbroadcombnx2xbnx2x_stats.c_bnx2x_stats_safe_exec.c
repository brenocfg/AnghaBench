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
struct bnx2x {int /*<<< orphan*/  stats_lock; scalar_t__ stats_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  bnx2x_stats_comp (struct bnx2x*) ; 
 scalar_t__ bnx2x_storm_stats_update (struct bnx2x*) ; 
 int down_timeout (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int bnx2x_stats_safe_exec(struct bnx2x *bp,
			  void (func_to_exec)(void *cookie),
			  void *cookie)
{
	int cnt = 10, rc = 0;

	/* Wait for statistics to end [while blocking further requests],
	 * then run supplied function 'safely'.
	 */
	rc = down_timeout(&bp->stats_lock, HZ / 10);
	if (unlikely(rc)) {
		BNX2X_ERR("Failed to take statistics lock for safe execution\n");
		goto out_no_lock;
	}

	bnx2x_stats_comp(bp);
	while (bp->stats_pending && cnt--)
		if (bnx2x_storm_stats_update(bp))
			usleep_range(1000, 2000);
	if (bp->stats_pending) {
		BNX2X_ERR("Failed to wait for stats pending to clear [possibly FW is stuck]\n");
		rc = -EBUSY;
		goto out;
	}

	func_to_exec(cookie);

out:
	/* No need to restart statistics - if they're enabled, the timer
	 * will restart the statistics.
	 */
	up(&bp->stats_lock);
out_no_lock:
	return rc;
}