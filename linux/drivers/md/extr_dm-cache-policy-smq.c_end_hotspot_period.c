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
struct smq_policy {scalar_t__ next_hotspot_period; int /*<<< orphan*/  hotspot_stats; int /*<<< orphan*/  hotspot; int /*<<< orphan*/  nr_hotspot_blocks; int /*<<< orphan*/  hotspot_hit_bits; } ;

/* Variables and functions */
 scalar_t__ HOTSPOT_UPDATE_PERIOD ; 
 int /*<<< orphan*/  clear_bitset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  q_redistribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  update_level_jump (struct smq_policy*) ; 
 int /*<<< orphan*/  update_promote_levels (struct smq_policy*) ; 

__attribute__((used)) static void end_hotspot_period(struct smq_policy *mq)
{
	clear_bitset(mq->hotspot_hit_bits, mq->nr_hotspot_blocks);
	update_promote_levels(mq);

	if (time_after(jiffies, mq->next_hotspot_period)) {
		update_level_jump(mq);
		q_redistribute(&mq->hotspot);
		stats_reset(&mq->hotspot_stats);
		mq->next_hotspot_period = jiffies + HOTSPOT_UPDATE_PERIOD;
	}
}