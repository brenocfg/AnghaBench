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
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int const rss_queues; int /*<<< orphan*/  flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_FLAG_QUEUE_PAIRS ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 

void igb_set_flag_queue_pairs(struct igb_adapter *adapter,
			      const u32 max_rss_queues)
{
	struct e1000_hw *hw = &adapter->hw;

	/* Determine if we need to pair queues. */
	switch (hw->mac.type) {
	case e1000_82575:
	case e1000_i211:
		/* Device supports enough interrupts without queue pairing. */
		break;
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	default:
		/* If rss_queues > half of max_rss_queues, pair the queues in
		 * order to conserve interrupts due to limited supply.
		 */
		if (adapter->rss_queues > (max_rss_queues / 2))
			adapter->flags |= IGB_FLAG_QUEUE_PAIRS;
		else
			adapter->flags &= ~IGB_FLAG_QUEUE_PAIRS;
		break;
	}
}