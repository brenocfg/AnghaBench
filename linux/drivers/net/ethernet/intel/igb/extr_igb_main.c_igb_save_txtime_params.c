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
struct igb_ring {int launchtime_enable; } ;
struct igb_adapter {int num_tx_queues; struct igb_ring** tx_ring; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int igb_save_txtime_params(struct igb_adapter *adapter, int queue,
				  bool enable)
{
	struct igb_ring *ring;

	if (queue < 0 || queue > adapter->num_tx_queues)
		return -EINVAL;

	ring = adapter->tx_ring[queue];
	ring->launchtime_enable = enable;

	return 0;
}