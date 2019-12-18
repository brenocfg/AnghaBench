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
struct smq_policy {scalar_t__ next_cache_period; int /*<<< orphan*/  cache_stats; int /*<<< orphan*/  clean; int /*<<< orphan*/  dirty; int /*<<< orphan*/  cache_size; int /*<<< orphan*/  cache_hit_bits; } ;

/* Variables and functions */
 scalar_t__ CACHE_UPDATE_PERIOD ; 
 int /*<<< orphan*/  clear_bitset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  q_redistribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void end_cache_period(struct smq_policy *mq)
{
	if (time_after(jiffies, mq->next_cache_period)) {
		clear_bitset(mq->cache_hit_bits, from_cblock(mq->cache_size));

		q_redistribute(&mq->dirty);
		q_redistribute(&mq->clean);
		stats_reset(&mq->cache_stats);

		mq->next_cache_period = jiffies + CACHE_UPDATE_PERIOD;
	}
}