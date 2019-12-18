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
typedef  int u32 ;
struct igc_adapter {int const rss_queues; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_FLAG_QUEUE_PAIRS ; 

void igc_set_flag_queue_pairs(struct igc_adapter *adapter,
			      const u32 max_rss_queues)
{
	/* Determine if we need to pair queues. */
	/* If rss_queues > half of max_rss_queues, pair the queues in
	 * order to conserve interrupts due to limited supply.
	 */
	if (adapter->rss_queues > (max_rss_queues / 2))
		adapter->flags |= IGC_FLAG_QUEUE_PAIRS;
	else
		adapter->flags &= ~IGC_FLAG_QUEUE_PAIRS;
}