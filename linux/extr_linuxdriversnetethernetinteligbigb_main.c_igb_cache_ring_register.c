#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct igb_adapter {int rss_queues; int num_rx_queues; int num_tx_queues; TYPE_4__** tx_ring; TYPE_3__** rx_ring; scalar_t__ vfs_allocated_count; TYPE_2__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg_idx; } ;
struct TYPE_7__ {scalar_t__ reg_idx; } ;

/* Variables and functions */
 scalar_t__ Q_IDX_82576 (int) ; 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 

__attribute__((used)) static void igb_cache_ring_register(struct igb_adapter *adapter)
{
	int i = 0, j = 0;
	u32 rbase_offset = adapter->vfs_allocated_count;

	switch (adapter->hw.mac.type) {
	case e1000_82576:
		/* The queues are allocated for virtualization such that VF 0
		 * is allocated queues 0 and 8, VF 1 queues 1 and 9, etc.
		 * In order to avoid collision we start at the first free queue
		 * and continue consuming queues in the same sequence
		 */
		if (adapter->vfs_allocated_count) {
			for (; i < adapter->rss_queues; i++)
				adapter->rx_ring[i]->reg_idx = rbase_offset +
							       Q_IDX_82576(i);
		}
		/* Fall through */
	case e1000_82575:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		/* Fall through */
	default:
		for (; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->reg_idx = rbase_offset + i;
		for (; j < adapter->num_tx_queues; j++)
			adapter->tx_ring[j]->reg_idx = rbase_offset + j;
		break;
	}
}