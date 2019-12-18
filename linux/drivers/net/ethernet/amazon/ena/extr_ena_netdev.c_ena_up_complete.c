#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ena_adapter {TYPE_1__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_change_mtu (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_napi_enable_all (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_refill_all_rx_bufs (struct ena_adapter*) ; 
 int ena_rss_configure (struct ena_adapter*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (TYPE_1__*) ; 

__attribute__((used)) static int ena_up_complete(struct ena_adapter *adapter)
{
	int rc;

	rc = ena_rss_configure(adapter);
	if (rc)
		return rc;

	ena_change_mtu(adapter->netdev, adapter->netdev->mtu);

	ena_refill_all_rx_bufs(adapter);

	/* enable transmits */
	netif_tx_start_all_queues(adapter->netdev);

	ena_napi_enable_all(adapter);

	return 0;
}