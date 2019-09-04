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
struct ena_ring {int ring_size; int /*<<< orphan*/  netdev; int /*<<< orphan*/  adapter; } ;
struct ena_adapter {int num_queues; struct ena_ring* rx_ring; } ;

/* Variables and functions */
 int ena_refill_rx_bufs (struct ena_ring*,int) ; 
 int /*<<< orphan*/  netif_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  rx_status ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ena_refill_all_rx_bufs(struct ena_adapter *adapter)
{
	struct ena_ring *rx_ring;
	int i, rc, bufs_num;

	for (i = 0; i < adapter->num_queues; i++) {
		rx_ring = &adapter->rx_ring[i];
		bufs_num = rx_ring->ring_size - 1;
		rc = ena_refill_rx_bufs(rx_ring, bufs_num);

		if (unlikely(rc != bufs_num))
			netif_warn(rx_ring->adapter, rx_status, rx_ring->netdev,
				   "refilling Queue %d failed. allocated %d buffers from: %d\n",
				   i, rc, bufs_num);
	}
}