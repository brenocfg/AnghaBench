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
struct sk_buff {unsigned int queue_mapping; } ;
struct igc_ring {int dummy; } ;
struct igc_adapter {unsigned int num_tx_queues; struct igc_ring** tx_ring; } ;

/* Variables and functions */

__attribute__((used)) static inline struct igc_ring *igc_tx_queue_mapping(struct igc_adapter *adapter,
						    struct sk_buff *skb)
{
	unsigned int r_idx = skb->queue_mapping;

	if (r_idx >= adapter->num_tx_queues)
		r_idx = r_idx % adapter->num_tx_queues;

	return adapter->tx_ring[r_idx];
}