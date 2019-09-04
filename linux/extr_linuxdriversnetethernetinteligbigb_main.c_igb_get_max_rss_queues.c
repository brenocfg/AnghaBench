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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  vfs_allocated_count; struct e1000_hw hw; } ;

/* Variables and functions */
 unsigned int IGB_MAX_RX_QUEUES ; 
 unsigned int IGB_MAX_RX_QUEUES_82575 ; 
 unsigned int IGB_MAX_RX_QUEUES_I211 ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 

unsigned int igb_get_max_rss_queues(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned int max_rss_queues;

	/* Determine the maximum number of RSS queues supported. */
	switch (hw->mac.type) {
	case e1000_i211:
		max_rss_queues = IGB_MAX_RX_QUEUES_I211;
		break;
	case e1000_82575:
	case e1000_i210:
		max_rss_queues = IGB_MAX_RX_QUEUES_82575;
		break;
	case e1000_i350:
		/* I350 cannot do RSS and SR-IOV at the same time */
		if (!!adapter->vfs_allocated_count) {
			max_rss_queues = 1;
			break;
		}
		/* fall through */
	case e1000_82576:
		if (!!adapter->vfs_allocated_count) {
			max_rss_queues = 2;
			break;
		}
		/* fall through */
	case e1000_82580:
	case e1000_i354:
	default:
		max_rss_queues = IGB_MAX_RX_QUEUES;
		break;
	}

	return max_rss_queues;
}