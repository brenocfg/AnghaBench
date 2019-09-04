#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_adapter {int num_rx_queues; int num_tx_queues; int num_xdp_queues; TYPE_3__** xdp_ring; TYPE_2__** tx_ring; int /*<<< orphan*/  netdev; TYPE_1__** rx_ring; } ;
struct TYPE_6__ {int reg_idx; } ;
struct TYPE_5__ {int reg_idx; } ;
struct TYPE_4__ {int reg_idx; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */

__attribute__((used)) static bool ixgbe_cache_ring_rss(struct ixgbe_adapter *adapter)
{
	int i, reg_idx;

	for (i = 0; i < adapter->num_rx_queues; i++) {
		adapter->rx_ring[i]->reg_idx = i;
		adapter->rx_ring[i]->netdev = adapter->netdev;
	}
	for (i = 0, reg_idx = 0; i < adapter->num_tx_queues; i++, reg_idx++)
		adapter->tx_ring[i]->reg_idx = reg_idx;
	for (i = 0; i < adapter->num_xdp_queues; i++, reg_idx++)
		adapter->xdp_ring[i]->reg_idx = reg_idx;

	return true;
}