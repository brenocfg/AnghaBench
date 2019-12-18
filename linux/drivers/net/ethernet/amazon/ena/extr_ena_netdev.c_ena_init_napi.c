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
struct ena_napi {int qid; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  napi; } ;
struct ena_adapter {int num_queues; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; struct ena_napi* ena_napi; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_NAPI_BUDGET ; 
 int /*<<< orphan*/  ena_io_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_init_napi(struct ena_adapter *adapter)
{
	struct ena_napi *napi;
	int i;

	for (i = 0; i < adapter->num_queues; i++) {
		napi = &adapter->ena_napi[i];

		netif_napi_add(adapter->netdev,
			       &adapter->ena_napi[i].napi,
			       ena_io_poll,
			       ENA_NAPI_BUDGET);
		napi->rx_ring = &adapter->rx_ring[i];
		napi->tx_ring = &adapter->tx_ring[i];
		napi->qid = i;
	}
}