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
struct ibmvnic_rx_pool {int size; struct ibmvnic_rx_pool* rx_buff; int /*<<< orphan*/ * skb; int /*<<< orphan*/  long_term_buff; struct ibmvnic_rx_pool* free_map; } ;
struct ibmvnic_adapter {int num_active_rx_pools; struct ibmvnic_rx_pool* rx_pool; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_long_term_buff (struct ibmvnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ibmvnic_rx_pool*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void release_rx_pools(struct ibmvnic_adapter *adapter)
{
	struct ibmvnic_rx_pool *rx_pool;
	int i, j;

	if (!adapter->rx_pool)
		return;

	for (i = 0; i < adapter->num_active_rx_pools; i++) {
		rx_pool = &adapter->rx_pool[i];

		netdev_dbg(adapter->netdev, "Releasing rx_pool[%d]\n", i);

		kfree(rx_pool->free_map);
		free_long_term_buff(adapter, &rx_pool->long_term_buff);

		if (!rx_pool->rx_buff)
			continue;

		for (j = 0; j < rx_pool->size; j++) {
			if (rx_pool->rx_buff[j].skb) {
				dev_kfree_skb_any(rx_pool->rx_buff[j].skb);
				rx_pool->rx_buff[j].skb = NULL;
			}
		}

		kfree(rx_pool->rx_buff);
	}

	kfree(adapter->rx_pool);
	adapter->rx_pool = NULL;
	adapter->num_active_rx_pools = 0;
}