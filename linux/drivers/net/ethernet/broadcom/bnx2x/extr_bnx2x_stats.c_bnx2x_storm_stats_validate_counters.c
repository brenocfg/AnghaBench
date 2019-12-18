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
typedef  scalar_t__ u16 ;
struct stats_counter {int /*<<< orphan*/  tstats_counter; int /*<<< orphan*/  cstats_counter; int /*<<< orphan*/  ustats_counter; int /*<<< orphan*/  xstats_counter; } ;
struct bnx2x {int /*<<< orphan*/  stats_counter; TYPE_1__* fw_stats_data; } ;
struct TYPE_2__ {struct stats_counter storm_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_STATS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_storm_stats_validate_counters(struct bnx2x *bp)
{
	struct stats_counter *counters = &bp->fw_stats_data->storm_counters;
	u16 cur_stats_counter;
	/* Make sure we use the value of the counter
	 * used for sending the last stats ramrod.
	 */
	cur_stats_counter = bp->stats_counter - 1;

	/* are storm stats valid? */
	if (le16_to_cpu(counters->xstats_counter) != cur_stats_counter) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by xstorm  xstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->xstats_counter), bp->stats_counter);
		return -EAGAIN;
	}

	if (le16_to_cpu(counters->ustats_counter) != cur_stats_counter) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by ustorm  ustorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->ustats_counter), bp->stats_counter);
		return -EAGAIN;
	}

	if (le16_to_cpu(counters->cstats_counter) != cur_stats_counter) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by cstorm  cstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->cstats_counter), bp->stats_counter);
		return -EAGAIN;
	}

	if (le16_to_cpu(counters->tstats_counter) != cur_stats_counter) {
		DP(BNX2X_MSG_STATS,
		   "stats not updated by tstorm  tstorm counter (0x%x) != stats_counter (0x%x)\n",
		   le16_to_cpu(counters->tstats_counter), bp->stats_counter);
		return -EAGAIN;
	}
	return 0;
}